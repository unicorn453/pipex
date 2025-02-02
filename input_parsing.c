/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:31 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/30 20:32:23 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**allocate_args_and_token(char **token)
{
	char	**args;

	args = malloc(1024 * sizeof(char *));
	if (!args)
	{
		args = NULL;
		return (args);
	}
	*token = malloc(1024);
	if (!*token)
	{
		free(args);
		args = NULL;
		return (args);
	}
	return (args);
}

int	add_token_to_args(char **args, char *token, int *arg_index,
		int *token_index)
{
	token[*token_index] = '\0';
	args[(*arg_index)++] = ft_strdup(token);
	if (!args[(*arg_index) - 1] && (*arg_index) > 0)
	{
		return (-1);
	}
	else if (!args[(*arg_index) - 1] && (*arg_index) == 0)
	{
		return (-2);
	}
	*token_index = 0;
	return (0);
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

char	**split_commands(const char *command)
{
	char		**args;
	char		*token;
	t_parser	*parser;
	int			check;

	check = 0;
	args = allocate_args_and_token(&token);
	if (!args)
		return (args);
	parser = initialize_parser(command, args, token);
	if (!parser)
	{
		free(args);
		return (args = NULL, args);
	}
	check = parse_command(parser);
	if (check == -1)
	{
		free(parser);
		free(token);
		free_args(args);
		return (args = NULL, args);
	}
	else if (check == -2)
	{
		free(parser);
		free(args);
		free(token);
		return (args = NULL, args);
	}
	free(token);
	free(parser);
	return (args);
}

t_parse	*init_parse(char *file, char *commands, bool input)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (parse = NULL, parse);
	parse->input = input;
	parse->file = ft_strdup(file);
	if (!parse->file)
		return (free(parse), parse = NULL, parse);
	parse->args = split_commands(commands);
	if (!parse->args)
	{
		free(parse->file);
		return (free(parse), parse = NULL, parse);
	}
	parse->cmd = ft_strdup(parse->args[0]);
	if (!parse->cmd)
	{
		free_args(parse->args);
		free(parse->cmd);
		free(parse->file);
		return (free(parse), parse = NULL, parse);
	}
	return (parse);
}
