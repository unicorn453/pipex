/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_err_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:13:25 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/30 17:31:39 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*add_permission_free_path(t_path *path, char *cmd)
{
	path->i = 0;
	while (path->paths[path->i])
	{
		path->temp = ft_strjoin(path->paths[path->i], "/");
		if (!path->temp)
		{
			free_paths(path, 1);
		}
		path->full_path = ft_strjoin(path->temp, cmd);
		free(path->temp);
		if (!path->full_path)
		{
			free_paths(path, 1);
		}
		if (access(path->full_path, X_OK) == 0)
		{
			free_paths(path, 0);
			return (path->full_path);
		}
		unlink(path->full_path);
		free(path->full_path);
		path->full_path = NULL;
		path->i++;
	}
	return (NULL);
}

void	free_cmd_err(t_cmd *cmd, t_pid *pid_info, int error_bool)
{
	if (pid_info)
		free(pid_info);
	if (cmd)
	{
		if (cmd->parse[0]->args)
			free_args(cmd->parse[0]->args);
		if (cmd->parse[1]->args)
			free_args(cmd->parse[1]->args);
		if (cmd->parse[0]->cmd)
			free(cmd->parse[0]->cmd);
		if (cmd->parse[1]->cmd)
			free(cmd->parse[1]->cmd);
		if (cmd->parse[0]->file)
			free(cmd->parse[0]->file);
		if (cmd->parse[1]->file)
			free(cmd->parse[1]->file);
		if (cmd->parse[0])
			free(cmd->parse[0]);
		if (cmd->parse[1])
			free(cmd->parse[1]);
		free(cmd);
	}
	if (error_bool)
		error();
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

void	perror_exit(t_parse *parse)
{
	if (parse)
		free(parse);
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}
