/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:57:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/30 17:32:08 by kruseva          ###   ########.fr       */
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

int	child_proc_one(t_cmd *cmd, char **envp, int *pipefd, t_pid *pid_info)
{
	if (cmd->in_fd == -1)
	{
		free_cmd_err(cmd, pid_info, 0);
		return (exit(0), 0);
	}
	dup2(cmd->in_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	pid_info->cmd1_path = find_command_path(cmd->parse[0]->cmd, envp);
	if (!pid_info->cmd1_path)
	{
		free_cmd_err(cmd, pid_info, 0);
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (execve(pid_info->cmd1_path, cmd->parse[0]->args, envp) == -1)
	{
		free_cmd_err(cmd, pid_info, 0);
		free(pid_info->cmd1_path);
		error();
	}
	free(pid_info->cmd1_path);
	return (exit(0), 0);
}

int	child_proc_two(t_cmd *cmd, char **envp, int *pipefd, t_pid *pid_info)
{
	if (cmd->out_fd == -1)
	{
		return (exit(127), 0);
	}
	dup2(cmd->out_fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	pid_info->cmd2_path = find_command_path(cmd->parse[1]->cmd, envp);
	if (!pid_info->cmd2_path)
	{
		error();
	}
	if (execve(pid_info->cmd2_path, cmd->parse[1]->args, envp) == -1)
	{
		free(pid_info->cmd2_path);
		error();
	}
	free(pid_info->cmd2_path);
	return (exit(0), 0);
}

int	pipe_and_fork(t_cmd *cmd, char **envp, t_pid *pid_info)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	pid_info->pid1 = fork();
	if (pid_info->pid1 == -1)
		return (-1);
	if (pid_info->pid1 == 0)
		child_proc_one(cmd, envp, pipefd, pid_info);
	pid_info->pid2 = fork();
	if (pid_info->pid2 == -1)
		return (-1);
	if (pid_info->pid2 == 0)
		child_proc_two(cmd, envp, pipefd, pid_info);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}

t_cmd	*init_cmd(char **argv)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		error();
	cmd->parse[0] = init_parse(argv[1], argv[2], true);
	cmd->parse[1] = init_parse(argv[4], argv[3], false);
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
		error();
	pid_info = initialize_pid();
	cmd = init_cmd(argv);
	if (cmd->in_fd == -1)
		perror("\033[31mError");
	if (cmd->out_fd == -1)
	{
		free_cmd_err(cmd, pid_info, 1);
	}
	if (pipe_and_fork(cmd, envp, pid_info) == -1)
	{
		free_cmd_err(cmd, pid_info, 1);
	}
	waitpid(pid_info->pid1, &pid_info->status1, 0);
	waitpid(pid_info->pid2, &pid_info->status2, 0);
	exit_stat = exit_status(pid_info->status1, pid_info->status2);
	free_cmd_err(cmd, pid_info, 0);
	if (exit_stat)
		return (exit_stat);
	return (0);
}
