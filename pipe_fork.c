/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:20:45 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/30 19:22:26 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		write(2, "command not found\n", 18);
		exit(EXIT_FAILURE);
	}
	if (execve(pid_info->cmd1_path, cmd->parse[0]->args, envp) == -1)
	{
		free_cmd_err(cmd, pid_info, 0);
		free(pid_info->cmd1_path);
		write(2, "command not found\n", 18);
		exit(EXIT_FAILURE);
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
		write(2, "command not found\n", 18);
		exit(EXIT_FAILURE);
	}
	if (execve(pid_info->cmd2_path, cmd->parse[1]->args, envp) == -1)
	{
		free(pid_info->cmd2_path);
		write(2, "command not found\n", 18);
		exit(EXIT_FAILURE);
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
