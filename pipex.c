/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:57:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/25 20:47:55 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>

void	error(void)
{
	// perror("\033[31mError");
	strerror(errno);
	exit(EXIT_FAILURE);
}
// void	error(const char *message)
// {
// 	perror(message);
// 	exit(EXIT_FAILURE);
// }

int	exec_permissions_added(char *path)
{
	return (access(path, X_OK) == 0);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;
	char	*temp;

	path_env = NULL;
	paths = NULL;
	full_path = NULL;
	for (i = 0; envp[i]; i++)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
	}
	if (!path_env)
	{
		fprintf(stderr, "PATH environment variable not found\n");
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		error();
	for (i = 0; paths[i]; i++)
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
		{
			for (int j = 0; paths[j]; j++)
				free(paths[j]);
			free(paths);
			error();
		}
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
		{
			for (int j = 0; paths[j]; j++)
				free(paths[j]);
			free(paths);
			error();
		}
		if (exec_permissions_added(full_path))
		{
			for (int j = 0; paths[j]; j++)
				free(paths[j]);
			free(paths);
			return (full_path);
		}
		unlink(full_path);
		free(full_path);
		full_path = NULL;
	}
	for (i = 0; paths[i]; i++)
		free(paths[i]);
	free(paths);
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
		{
			// perror("open");
			return (-1);
		}
	}
	else if (mode == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			// perror("open");
			return (-1);
		}
	}
	else
	{
		fd = -1;
	}
	return (fd);
}

void	pipe_and_fork(t_cmd *cmd, char **envp)
{
	char	*cmd_path;
	int		pipefd[2];
	pid_t	pid;

	cmd_path = NULL;
	if (pipe(pipefd) == -1)
	{
		// perror("pipe");
		error();
	}
	pid = fork();
	if (pid == -1)
	{
		// perror("fork");
		error();
	}
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		// Find the command path
		cmd_path = find_command_path(cmd->parse[0]->cmd, envp);
		if (!cmd_path)
		{
			error();
		}
		if (execve(cmd_path, cmd->parse[0]->args, envp) == -1)
		{
			free(cmd_path);
			error();
		}
		free(cmd_path);
		error();
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		cmd_path = find_command_path(cmd->parse[1]->cmd, envp);
		if (!cmd_path)
		{
			error();
		}
		if (execve(cmd_path, cmd->parse[1]->args, envp) == -1)
		{
			free(cmd_path);
			error();
		}
		free(cmd_path);
		error();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	int		in_fd;
	int		out_fd;

	if (argc != 5)
	{
		error();
	}
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		// perror("malloc");
		error();
	}
	cmd->parse[0] = init_parse(argv[1], argv[2], true);
	cmd->parse[1] = init_parse(argv[4], argv[3], false);
	cmd->fd_in = argv[1];
	cmd->fd_out = argv[4];
	in_fd = ft_in_out(cmd->fd_in, 0);
	if (in_fd == -1)
	{
		free(cmd->parse[0]);
		free(cmd->parse[1]);
		free(cmd);
		error();
	}
	out_fd = ft_in_out(cmd->fd_out, 1);
	if (out_fd == -1)
	{
		free(cmd->parse[0]);
		free(cmd->parse[1]);
		free(cmd);
		error();
	}
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	pipe_and_fork(cmd, envp);
	close(in_fd);
	close(out_fd);
	free(cmd->parse[0]);
	free(cmd->parse[1]);
	free(cmd);
	return (0);
}
