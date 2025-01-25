/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:59:21 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/25 20:37:05 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include "./libft/libft.h"
#include "./libft/ft_printf/ft_printf.h"
#include "./libft/get_next_line/get_next_line.h"

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

t_parse *init_parse(char *file, char *commands, bool input);
void	error(void);