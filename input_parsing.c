/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:31 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/27 20:40:16 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(void)
{
	// free(parse);
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

bool *process_char(char c, const char *command, int *i, char *token, int *token_index)
{
    static bool checks[3] = {false, false, false};

    if (c == '\\' && (command[*i + 1] == '"' || command[*i + 1] == '\'')) {
        checks[2] = true;
        (*i)++;
        token[(*token_index)++] = command[*i];
        return checks;
    }

    if ((c == '\'' || c == '"') && checks[2]) {
        checks[2] = false;
        return checks;
    }

    if (c == '\'' && !checks[1] && !checks[2]) {
        checks[0] = !checks[0];
        return checks;
    }

    if (c == '"' && !checks[0] && !checks[2]) {
        checks[1] = !checks[1];
        return checks;
    }

    if (c == ' ' && !checks[0] && !checks[1] && !checks[2]) {
        return checks;
    }

    token[(*token_index)++] = c;
    checks[2] = false;
    return checks;
}

char **split_commands(const char *command);
char **allocate_args_and_token();
void free_args_and_token(char **args, char *token);
void add_token_to_args(char **args, char *token, int *arg_index, int *token_index);

 void parse_command(const char *command, char **args, char *token, int *arg_index, int *token_index)
    {
        bool checks[3] = {false, false, false};
        char c;
        int i = 0;
        while (command[i] != '\0') {
            c = command[i];
           bool *temp_checks = process_char(c, command, &i, token, token_index);
           for (int j = 0; j < 3; j++) {
               checks[j] = temp_checks[j];
           }

            if (c == ' ' && !checks[0] && !checks[1] && !checks[2]) {
            if (*token_index > 0) { 
                add_token_to_args(args, token, arg_index, token_index);
            }
            }
            i++;
        }
    }


char **split_commands(const char *command)
{
    char **args;
    char *token;
    int arg_index = 0;
    int token_index = 0;
    // bool checks[3] = {false, false, false};

    args = allocate_args_and_token(&token);
    if (!args || !token) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

//    parse_command(command, args, token, &arg_index, &token_index, checks);

parse_command(command, args, token, &arg_index, &token_index);

    if (token_index > 0) {
        add_token_to_args(args, token, &arg_index, &token_index);
    }

    args[arg_index] = NULL;

    free(token);

    return args;
}

char **allocate_args_and_token(char **token)
{
    char **args = malloc(1024 * sizeof(char *));
    *token = malloc(1024);
    return args;
}

void add_token_to_args(char **args, char *token, int *arg_index, int *token_index)
{
    token[*token_index] = '\0';
    args[(*arg_index)++] = strdup(token);
    *token_index = 0;
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
