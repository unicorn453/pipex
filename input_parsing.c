/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:31 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/27 23:23:29 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(t_parse *parse)
{
	if (parse)
		free(parse);
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	**allocate_args_and_token(char **token)
{
	char	**args;

	args = malloc(1024 * sizeof(char *));
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	*token = malloc(1024);
	if (!*token)
	{
		free(args);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (args);
}

void	add_token_to_args(char **args, char *token, int *arg_index,
		int *token_index)
{
	token[*token_index] = '\0';
	args[(*arg_index)++] = strdup(token);
	*token_index = 0;
}

bool	handle_escape(t_parser *parser)
{
	char	next_char;
	char	current_char;

	next_char = parser->command[parser->i + 1];
	current_char = parser->command[parser->i];
	if (current_char == '\\' && (next_char == '"' || next_char == '\''))
	{
		parser->checks[2] = true;
		parser->i++;
		parser->token[parser->token_index++] = next_char;
		return (true);
	}
	return (false);
}

bool	handle_quotes(char c, bool *checks)
{
	if ((c == '\'' || c == '"') && checks[2])
	{
		checks[2] = false;
		return (true);
	}
	if (c == '\'' && !checks[1] && !checks[2])
	{
		checks[0] = !checks[0];
		return (true);
	}
	if (c == '"' && !checks[0] && !checks[2])
	{
		checks[1] = !checks[1];
		return (true);
	}
	return (false);
}

bool	handle_space(char c, bool *checks)
{
	if (c == ' ' && !checks[0] && !checks[1] && !checks[2])
		return (true);
	return (false);
}

bool	*process_char(t_parser *parser)
{
	char	c;

	c = parser->command[parser->i];
	if (handle_escape(parser) || handle_quotes(c, parser->checks)
		|| handle_space(c, parser->checks))
		return (parser->checks);
	parser->token[parser->token_index++] = c;
	parser->checks[2] = false;
	return (parser->checks);
}

void	parse_command(t_parser *parser)
{
	while (parser->command[parser->i] != '\0')
	{
		parser->c = parser->command[parser->i];
		process_char(parser);
		if (handle_space(parser->c, parser->checks) && parser->token_index > 0)
		{
			add_token_to_args(parser->args, parser->token, &parser->arg_index,
				&parser->token_index);
		}
		parser->i++;
	}
	if (parser->token_index > 0)
	{
		add_token_to_args(parser->args, parser->token, &parser->arg_index,
			&parser->token_index);
	}
	parser->args[parser->arg_index] = NULL;
}

t_parser	*initialize_parser(const char *command, char **args, char *token)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	parser->command = command;
	parser->i = 0;
	parser->token = token;
	parser->token_index = 0;
	parser->args = args;
	parser->arg_index = 0;
	parser->checks[0] = false;
	parser->checks[1] = false;
	parser->checks[2] = false;
	return (parser);
}

char	**split_commands(const char *command)
{
	char		**args;
	char		*token;
	t_parser	*parser;

	args = allocate_args_and_token(&token);
	parser = initialize_parser(command, args, token);
	parse_command(parser);
	free(token);
	free(parser);
	return (args);
}

t_parse	*init_parse(char *file, char *commands, bool input)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		error();
	parse->input = input;
	parse->file = strdup(file);
	if (!parse->file)
		perror_exit(parse);
	parse->args = split_commands(commands);
	if (!parse->args)
	{
		free(parse->file);
		perror_exit(parse);
	}
	parse->cmd = strdup(parse->args[0]);
	if (!parse->cmd)
	{
		free_args(parse->args);
		free(parse->file);
		perror_exit(parse);
	}
	return (parse);
}
