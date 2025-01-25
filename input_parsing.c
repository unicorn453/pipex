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

void perror_exit(t_parse *parse)
{
    free(parse);
    // perror(name);

   perror("\033[31mError");
    exit(EXIT_FAILURE);
}

t_parse *init_parse(char *file, char *commands, bool input)
{
    t_parse *parse = malloc(sizeof(t_parse));
    if (!parse)
    {
        // perror("malloc");
       perror("\033[31mError");
        exit(EXIT_FAILURE);
    }

    parse->input = input;
    parse->file = ft_strdup(file);
    if (!parse->file)
        perror_exit(parse);

    char **str = ft_split(commands, ' ');
    if (!str)
        perror_exit(parse);

    parse->cmd = ft_strdup(str[0]);
    if (!parse->cmd)
        perror_exit(parse);
int num_tokens = 0;
    for (int i = 0; str[i]; i++)
        num_tokens++;
parse->args = malloc(sizeof(char *) * (num_tokens + 1));
for(int i = 0; str[i]; i++)
{
    parse->args[i] = ft_strdup(str[i]);
    if (!parse->args[i])
        perror_exit(parse);
}
parse->args[num_tokens] = NULL;

    return parse;
}
