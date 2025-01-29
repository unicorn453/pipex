/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:06:40 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/29 15:08:13 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pid	*initialize_pid(void)
{
	t_pid	*pid_info;

	pid_info = malloc(sizeof(t_pid));
	if (!pid_info)
		error();
	pid_info->pid1 = -1;
	pid_info->pid2 = -1;
	pid_info->cmd1_path = NULL;
	pid_info->cmd2_path = NULL;
	pid_info->status1 = 0;
	pid_info->status2 = 0;
	return (pid_info);
}

t_path	*initialize_path(void)
{
	t_path	*path;

	path = malloc(sizeof(t_path));
	if (!path)
		error();
	path->path_env = NULL;
	path->paths = NULL;
	path->full_path = NULL;
	path->i = 0;
	path->temp = NULL;
	return (path);
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

void	free_paths(t_path *path, int error_bool)
{
	int	j;

	j = 0;
	while (path->paths[j])
	{
		free(path->paths[j]);
		j++;
	}
	free(path->paths);
	if (error_bool)
		error();
}
