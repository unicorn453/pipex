/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:57:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/28 16:16:03 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command_path(char *cmd, char **envp)
{
	t_path	*path;

	path = initialize_path();
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
		error();
	path->paths = ft_split(path->path_env, ':');
	if (!path->paths)
		error();
	path->full_path = add_permission_free_path(path, cmd);
	if (path->full_path)
		return (path->full_path);
	free_paths(path, 0);
	free(path);
	fprintf(stderr, "Command not found: %s\n", cmd);
	return (NULL);
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

void	exec_cmd(t_cmd *cmd, char **envp, int *pipefd, t_pid *pid_info)
{
	if (pid_info->pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		pid_info->cmd1_path = find_command_path(cmd->parse[0]->cmd, envp);
		if (!pid_info->cmd1_path)
			error();
		if (execve(pid_info->cmd1_path, cmd->parse[0]->args, envp) == -1)
			error();
	}
	pid_info->pid2 = fork();
	if (pid_info->pid2 == -1)
		error();
	if (pid_info->pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		pid_info->cmd2_path = find_command_path(cmd->parse[1]->cmd, envp);
		if (!pid_info->cmd2_path)
			error();
		if (execve(pid_info->cmd2_path, cmd->parse[1]->args, envp) == -1)
			error();
	}
}

void	pipe_and_fork(t_cmd *cmd, char **envp)
{
	t_pid	*pid_info;
	int		pipefd[2];

	pid_info = initialize_pid();
	if (pipe(pipefd) == -1)
		error();
	pid_info->pid1 = fork();
	if (pid_info->pid1 == -1)
		error();
	exec_cmd(cmd, envp, pipefd, pid_info);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_info->pid1, &pid_info->status1, 0);
	waitpid(pid_info->pid2, &pid_info->status2, 0);
	if (WIFEXITED(pid_info->status1) && WEXITSTATUS(pid_info->status1) != 0)
		exit(WEXITSTATUS(pid_info->status1));
	else if (WIFEXITED(pid_info->status2)
		&& WEXITSTATUS(pid_info->status2) != 0)
		exit(WEXITSTATUS(pid_info->status2));
	else
		exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	int		in_fd;
	int		out_fd;

	if (argc != 5)
		error();
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		error();
	cmd->parse[0] = init_parse(argv[1], argv[2], true);
	cmd->parse[1] = init_parse(argv[4], argv[3], false);
	cmd->fd_in = argv[1];
	cmd->fd_out = argv[4];
	in_fd = ft_in_out(cmd->fd_in, 0);
	if (in_fd == -1)
		free_cmd_err(cmd, 1);
	out_fd = ft_in_out(cmd->fd_out, 1);
	if (out_fd == -1)
		free_cmd_err(cmd, 1);
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	pipe_and_fork(cmd, envp);
	return (close(in_fd), close(out_fd), free_cmd_err(cmd, 0), 0);
}
