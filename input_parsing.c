/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:34:31 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/25 20:33:21 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(void)
{
	// free(parse);
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

t_parse	*init_parse(char *file, char *commands, bool input)
{
	t_parse	*parse;
	char	**str;
	int		num_tokens;

	parse = malloc(sizeof(t_parse));
	if (!parse)
	{
		// perror("malloc");
		perror("\033[31mError");
		exit(EXIT_FAILURE);
	}
	parse->input = input;
	parse->file = ft_strdup(file);
	if (!parse->file)
	{
		free(parse);
		perror_exit();
	}
	str = ft_split(commands, ' ');
	if (!str)
	{
		free(parse);
		perror_exit();
	}
	parse->cmd = ft_strdup(str[0]);
	if (!parse->cmd)
	{
		free(parse);
		perror_exit();
	}
	num_tokens = 0;
	for (int i = 0; str[i]; i++)
		num_tokens++;
	parse->args = malloc(sizeof(char *) * (num_tokens + 1));
	for (int i = 0; str[i]; i++)
	{
		parse->args[i] = ft_strdup(str[i]);
		if (!parse->args[i])
		{
			free(parse);
			perror_exit();
		}
	}
	parse->args[num_tokens] = NULL;
	return (parse);
}
