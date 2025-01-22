/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:57:41 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/18 00:23:13 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_substrings(const char *s, char c)

{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	*allocate_substring(const char *start, int length)
{
	char	*substr;

	substr = (char *)malloc((length + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, start, length + 1);
	return (substr);
}

static int	process_substring(char **result, int *j, const char *s, char c)
{
	int	i;
	int	start;

	i = 0;
	while (s[i] == c)
		i++;
	start = i;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (start < i)
	{
		result[*j] = allocate_substring(s + start, i - start);
		if (!result[*j])
			return (-1);
		(*j)++;
	}
	return (i);
}

static char	**free_result(char **result, int j)
{
	while (j > 0)
		free(result[--j]);
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		substring_count;
	int		i;
	int		j;
	int		processed;

	if (!s)
		return (NULL);
	substring_count = count_substrings(s, c);
	result = (char **)malloc((substring_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < substring_count)
	{
		processed = process_substring(result, &j, s + i, c);
		if (processed == -1)
			return (free_result(result, j));
		i += processed;
	}
	result[j] = NULL;
	return (result);
}
