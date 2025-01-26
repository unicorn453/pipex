/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:31 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/25 20:33:21 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(void)
{
	// free(parse);
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char **split_commands(const char *command)
{
    char **args;
    char *token;
    int arg_index = 0;
    int token_index = 0;
    bool in_single_quote = false;
    bool in_double_quote = false;
    bool in_escaped = false; // To track escape sequences
    char c;

    args = malloc(1024 * sizeof(char *));  // Allocate memory for tokens
    token = malloc(1024);  // Allocate memory for a single token
    if (!args || !token) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; command[i] != '\0'; i++) {
        c = command[i];

    
        if (c == '\\' && (command[i + 1] == '"' || command[i + 1] == '\'')) {
            in_escaped = true;
            i++;
            token[token_index++] = command[i];
            continue;
        }

        if ((c == '\'' || c == '"') && in_escaped) {
            in_escaped = false;
            continue;
        }

        if (c == '\'' && !in_double_quote && !in_escaped) {
            in_single_quote = !in_single_quote;
            continue;
        }

        if (c == '"' && !in_single_quote && !in_escaped) {
            in_double_quote = !in_double_quote;
            continue;
        }

        if (c == ' ' && !in_single_quote && !in_double_quote && !in_escaped) {
            if (token_index > 0) { 
                token[token_index] = '\0';
                args[arg_index++] = strdup(token); 
                token_index = 0;
            }
            continue;
        }

        token[token_index++] = c;

        in_escaped = false;
    }

    if (token_index > 0) {
        token[token_index] = '\0';
        args[arg_index++] = strdup(token);
    }

    args[arg_index] = NULL;

    free(token);

    return args;
}




t_parse	*init_parse(char *file, char *commands, bool input)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	parse->input = input;
	parse->file = strdup(file);
	if (!parse->file)
	{
		free(parse);
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	parse->args = split_commands(commands);
	if (!parse->args)
	{
		free(parse);
		perror("split_commands");
		exit(EXIT_FAILURE);
	}
	parse->cmd = strdup(parse->args[0]);
	if (!parse->cmd)
	{
		for (int i = 0; parse->args[i]; i++)
			free(parse->args[i]);
		free(parse->args);
		free(parse);
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	return (parse);
}
