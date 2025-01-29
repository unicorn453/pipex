/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:31 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/28 16:23:58 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		free(parse->cmd);
		free(parse->file);
		perror_exit(parse);
	}
	return (parse);
}
