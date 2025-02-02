/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:57:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/30 20:06:20 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command_path(char *cmd, char **envp)
{
	t_path	*path;
	char	*ret_str;

	path = initialize_path();
	if (!path)
	{
		ret_str = NULL;
		return (ret_str);
	}
	path->i = 0;
	while (envp[path->i])
	{
		if (ft_strncmp(envp[path->i], "PATH=", 5) == 0)
		{
			path->path_env = envp[path->i] + 5;
			break ;
		}
		path->i++;
	}
	if (!path->path_env)
	{
		free(path);
		ret_str = NULL;
		return (ret_str);
	}
	path->paths = ft_split(path->path_env, ':');
	if (!path->paths)
	{
		free(path);
		ret_str = NULL;
		return (ret_str);
	}
	path->full_path = add_permission_free_path(path, cmd);
	if (path->full_path)
		return (path->full_path);
	free_paths(path, 0);
	free(path);
	ret_str = NULL;
	return (ret_str);
}

int	ft_in_out(char *file, int mode)
{
	int	fd;

	if (mode == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			return (-1);
	}
	else if (mode == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
	}
	else
	{
		fd = -1;
	}
	return (fd);
}

t_cmd	*init_cmd(char **argv)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (cmd = NULL, cmd);
	cmd->parse[0] = init_parse(argv[1], argv[2], true);
	cmd->parse[1] = init_parse(argv[4], argv[3], false);
	if (!cmd->parse[0] || !cmd->parse[1])
	{
		free(cmd);
		return (cmd = NULL, cmd);
	}
	cmd->fd_in = argv[1];
	cmd->fd_out = argv[4];
	cmd->envp = NULL;
	cmd->in_fd = ft_in_out(cmd->fd_in, 0);
	cmd->out_fd = ft_in_out(cmd->fd_out, 1);
	return (cmd);
}

int	exit_status(int status1, int status2)
{
	int	exit_status1;
	int	exit_status2;

	if (WIFEXITED(status1))
		exit_status1 = WEXITSTATUS(status1);
	else
		exit_status1 = 0;
	if (WIFEXITED(status2))
		exit_status2 = WEXITSTATUS(status2);
	else
		exit_status2 = 0;
	if (exit_status1 != 0 && exit_status2 != 0)
	{
		return (exit_status1);
	}
	if (exit_status1 != 0)
		return (exit_status1);
	if (exit_status2 != 0)
		return (exit_status2);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_pid	*pid_info;
	int		exit_stat;

	if (argc != 5)
	{
		write(2, "Error: wrong number of arguments\n", 34);
		exit(EXIT_FAILURE);
	}
	pid_info = initialize_pid();
	cmd = init_cmd(argv);
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
	if (pipe_and_fork(cmd, envp, pid_info) == -1)
		free_cmd_err(cmd, pid_info, 1);
	if ((waitpid(pid_info->pid1, &pid_info->status1, 0) == -1)
		|| (waitpid(pid_info->pid2, &pid_info->status2, 0)) == -1)
		free_cmd_err(cmd, pid_info, 1);
	exit_stat = exit_status(pid_info->status1, pid_info->status2);
	free_cmd_err(cmd, pid_info, 0);
	if (exit_stat)
		return (exit_stat);
	return (0);
}
