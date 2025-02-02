/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:06:40 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/02 17:59:33 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pid	*initialize_pid(void)
{
	t_pid	*pid_info;

	pid_info = malloc(sizeof(t_pid));
	if (!pid_info)
	{
		pid_info = NULL;
		return (pid_info);
	}
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
	{
		path = NULL;
		return (path);
	}
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
		parser = NULL;
		return (parser);
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
	if (!path || !path->paths)
		return ;
	while (path->paths[j])
	{
		free(path->paths[j]);
		path->paths[j] = NULL;
		j++;
	}
	free(path->paths);
	path->paths = NULL;
	if (error_bool)
		error();
}

void	check_pid_cmd(t_pid *pid_info, t_cmd *cmd)
{
	if (!pid_info)
	{
		write(2, "Error: malloc\n", 14);
		exit(EXIT_FAILURE);
	}
	if (!cmd)
	{
		free(pid_info);
		write(2, "Error: malloc\n", 14);
		exit(EXIT_FAILURE);
	}
	if (cmd->in_fd == -1)
		perror("\033[31mError");
	if (cmd->out_fd == -1)
		free_cmd_err(cmd, pid_info, 1);
}
