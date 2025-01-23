/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:57:00 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/23 18:58:32 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_parse {
    bool input;
    char *file;
    char *cmd;
    char *option;
    char *pattern;
    char **args; // To store arguments for execve
} t_parse;

// Has two parts because of the pipe
typedef struct s_cmd {
    t_parse *parse[2];
    char *fd_in;  // Input file path
    char *fd_out; // Output file path
} t_cmd;



int ft_in_out(char *file, int mode) {
    int fd;
    if (mode == 0) { // Input file
        fd = open(file, O_RDONLY);
        if (fd < 0) {
            perror("open");
            exit(1);
        }
    } else if (mode == 1) { // Output file
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            perror("open");
            exit(1);
        }
    } else {
        fd = -1;
    }
    return fd;
}

t_parse *init_parse(char *file, char *commands, bool input) {
    t_parse *parse = malloc(sizeof(t_parse));
    if (!parse) {
        perror("malloc");
        exit(1);
    }
    parse->input = input;
    parse->file = ft_strdup(file);
    if (!parse->file) {
        perror("ft_strdup");
        free(parse);
        exit(1);
    }

    char **str = ft_split(commands, ' ');
    if (!str) {
        perror("ft_split");
        free(parse);
        exit(1);
    }

    // Assign arguments based on space count
    parse->cmd = ft_strdup(str[0]);
    parse->args = str; // Save the entire split array for execve
    if (!parse->cmd) {
        perror("ft_strdup");
        free(parse);
        exit(1);
    }
    parse->option = (str[1]) ? ft_strdup(str[1]) : NULL;
    parse->pattern = (str[2]) ? ft_strdup(str[2]) : NULL;

    return parse;
}


void pipe_and_fork(t_cmd *cmd) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to write end of the pipe
        close(pipefd[0]);              // Close unused read end
        close(pipefd[1]);

        // Execute command
        execve(cmd->parse[0]->cmd, cmd->parse[0]->args, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to read end of the pipe
        close(pipefd[0]);
        close(pipefd[1]);

        // Wait for child process
        waitpid(pid, NULL, 0);

        // Execute second command
        execve(cmd->parse[1]->cmd, cmd->parse[1]->args, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s infile 'cmd1 args' 'cmd2 args' outfile\n", argv[0]);
        exit(1);
    }

    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd) {
        perror("malloc");
        exit(1);
    }

    // Initialize commands
    cmd->parse[0] = init_parse(argv[1], argv[2], true);  // First command
    cmd->parse[1] = init_parse(argv[4], argv[3], false); // Second command
    cmd->fd_in = argv[1];
    cmd->fd_out = argv[4];

    // Open input and output files
    int in_fd = ft_in_out(cmd->fd_in, 0);
    int out_fd = ft_in_out(cmd->fd_out, 1);

    // Redirect stdin and stdout
    dup2(in_fd, STDIN_FILENO);
    dup2(out_fd, STDOUT_FILENO);

    // Close file descriptors
    close(in_fd);
    close(out_fd);

    // Execute pipe and fork logic
    pipe_and_fork(cmd);

    // Free resources
    free(cmd->parse[0]);
    free(cmd->parse[1]);
    free(cmd);

    return 0;
}
