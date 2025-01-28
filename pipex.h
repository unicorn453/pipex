/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:59:21 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/28 15:53:06 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "./libft/libft.h"
#include "./libft/ft_printf/ft_printf.h"
#include "./libft/get_next_line/get_next_line.h"

typedef struct s_parse
{
	bool	input;
	char	*file;
	char	*cmd;
	char	*option;
	char	*pattern;
	char	**args;
}			t_parse;

typedef struct s_cmd
{
	t_parse	*parse[2];
	char	*fd_in;
	char	*fd_out;
	char	**envp;
}			t_cmd;

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

typedef struct s_pid{
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd1_path;
	char	*cmd2_path;
	int status1;
	int status2;
	} t_pid;

typedef struct s_path{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;
	char	*temp;
} t_path;

t_parse		*init_parse(char *file, char *commands, bool input);
void		error(void);
char	**split_commands(const char *command);
char	**allocate_args_and_token(char **token);
void	free_args_and_token(char **args, char *token);
void	add_token_to_args(char **args, char *token, int *arg_index,
			int *token_index);
