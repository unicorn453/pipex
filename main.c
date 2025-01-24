/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:57:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/24 16:58:07 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_parse
{
    bool input;
    char *file;
    char *cmd;
    char *option;
    char *pattern;
    char **args;
} t_parse;

typedef struct s_cmd
{
    t_parse *parse[2];
    char *fd_in;
    char *fd_out;
    char **envp;
} t_cmd;

int exec_permissions_added(char *path)
{
    int acc = access(path, X_OK);
    if (acc == 0)
        return 1;
    return 0;
}

char *find_command_path(char *cmd, char **envp)
{
    char *path_env = NULL;
    char **paths = NULL;
    char *full_path = NULL;
    int i = 0;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5;
            break;
        }
        i++;
    }

    if (!path_env)
        return NULL;

    paths = ft_split(path_env, ':');
    if (!paths)
    {
        perror("ft_split");
        exit(1);
    }

    for (i = 0; paths[i]; i++)
    {
        full_path = ft_strjoin(paths[i], "/");
        if (!full_path)
        {
            perror("ft_strjoin");
            exit(1);
        }

        char *temp = ft_strjoin(full_path, cmd);
        free(full_path);
        full_path = temp;

        if (!full_path)
        {
            perror("ft_strjoin");
            exit(1);
        }


        if (exec_permissions_added(full_path) == 1)
        {
            for (int j = 0; paths[j]; j++)
                free(paths[j]);
            free(paths);
            return full_path;
        }

        free(full_path);
        full_path = NULL;
    }

    for (i = 0; paths[i]; i++)
        free(paths[i]);
    free(paths);

    return NULL;
}



int ft_in_out(char *file, int mode)
{
    int fd;
    if (mode == 0)
    {
        fd = open(file, O_RDONLY);
        if (fd < 0)
        {
            perror("open");
            exit(1);
        }
    }
    else if (mode == 1)
    {
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("open");
            exit(1);
        }
    }
    else
    {
        fd = -1;
    }
    return fd;
}

t_parse *init_parse(char *file, char *commands, bool input)
{
    t_parse *parse = malloc(sizeof(t_parse));
    if (!parse)
    {
        perror("malloc");
        exit(1);
    }
    parse->input = input;
    parse->file = ft_strdup(file);
    if (!parse->file)
    {
        perror("ft_strdup");
        free(parse);
        exit(1);
    }

    char **str = ft_split(commands, ' ');
    if (!str)
    {
        perror("ft_split");
        free(parse);
        exit(1);
    }

    parse->cmd = ft_strdup(str[0]);
    parse->args = str;
    if (!parse->cmd)
    {
        perror("ft_strdup");
        free(parse);
        exit(1);
    }
    parse->option = (str[1]) ? ft_strdup(str[1]) : NULL;
    // printf("option: %s\n", parse->option);
    parse->pattern = (str[2]) ? ft_strdup(str[2]) : NULL;
    // printf("pattern: %s\n", parse->pattern);

    return parse;
}

void pipe_and_fork(t_cmd *cmd, char **envp)
{
    char *cmd_path = NULL;
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) 
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

       cmd_path = find_command_path(cmd->parse[0]->cmd, envp);
        if (!cmd_path)
        {
            perror("Command not found");
            exit(1);
        }

        execve(cmd_path, cmd->parse[0]->args, envp);
        perror("execve");
        free(cmd_path);
        exit(EXIT_FAILURE);
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
            perror("Command not found");
            exit(1);
        }
        execve(cmd_path, cmd->parse[1]->args, envp);
        perror("execve");
        free(cmd_path);
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char **argv, char **envp)
{
    if (argc != 5)
    {
        ft_printf( "Usage: %s infile 'cmd1 args' 'cmd2 args' outfile\n", argv[0]);
        exit(1);
    }
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd)
    {
        perror("malloc");
        exit(1);
    }

    cmd->parse[0] = init_parse(argv[1], argv[2], true);
    cmd->parse[1] = init_parse(argv[4], argv[3], false);
    cmd->fd_in = argv[1];
    cmd->fd_out = argv[4];
    int in_fd = ft_in_out(cmd->fd_in, 0);
    int out_fd = ft_in_out(cmd->fd_out, 1);
    dup2(in_fd, STDIN_FILENO);
    dup2(out_fd, STDOUT_FILENO);
    pipe_and_fork(cmd, envp);
    close(in_fd);
    close(out_fd);

    free(cmd->parse[0]);
    free(cmd->parse[1]);
    free(cmd);

    return 0;
}
