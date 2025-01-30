/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:59:21 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/30 19:21:57 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/ft_printf/ft_printf.h"
#include "./libft/get_next_line/get_next_line.h"
#include "./libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_parse
{
	bool		input;
	char		*file;
	char		*cmd;
	char		*option;
	char		*pattern;
	char		**args;
}				t_parse;

typedef struct s_cmd
{
	t_parse		*parse[2];
	char		*fd_in;
	char		*fd_out;
	char		**envp;
	int			in_fd;
	int			out_fd;
}				t_cmd;

typedef struct s_parser
{
	const char	*command;
	char		c;
	int			i;
	char		*token;
	int			token_index;
	char		**args;
	int			arg_index;
	bool		checks[3];
}				t_parser;

typedef struct s_pid
{
	pid_t		pid1;
	pid_t		pid2;
	char		*cmd1_path;
	char		*cmd2_path;
	int			status1;
	int			status2;
}				t_pid;

typedef struct s_path
{
	char		*path_env;
	char		**paths;
	char		*full_path;
	int			i;
	char		*temp;
}				t_path;

// init_stacks_free.c
t_pid			*initialize_pid(void);
t_path			*initialize_path(void);
t_parser		*initialize_parser(const char *command, char **args,
					char *token);
void			free_paths(t_path *path, int error_bool);

// free_err_functions.c
void			error(void);
void			perror_exit(t_parse *parse);
void			free_args(char **args);
void			free_cmd_err(t_cmd *cmd, t_pid *pid_info, int error_bool);
char			*add_permission_free_path(t_path *path, char *cmd);

// input_parsing.c
t_parse			*init_parse(char *file, char *commands, bool input);
char			**split_commands(const char *command);
bool			handle_escape(t_parser *parser);
void			add_token_to_args(char **args, char *token, int *arg_index,
					int *token_index);
char			**allocate_args_and_token(char **token);

// input_parsing_helper.c
void			parse_command(t_parser *parser);
bool			*process_char(t_parser *parser);
bool			handle_space(char c, bool *checks);
bool			handle_quotes(char c, bool *checks);

// pipe_fork.c
int				pipe_and_fork(t_cmd *cmd, char **envp, t_pid *pid_info);
int				child_proc_two(t_cmd *cmd, char **envp, int *pipefd,
					t_pid *pid_info);
int				child_proc_one(t_cmd *cmd, char **envp, int *pipefd,
					t_pid *pid_info);