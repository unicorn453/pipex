/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:43:10 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 20:43:17 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	to_find;
	char	*str;
	char	*found;
	size_t	string_len;

	to_find = c;
	str = (char *)s;
	string_len = sizeof(str);
	i = 0;
	while (i < n)
	{
		if (to_find == str[i])
		{
			found = &str[i];
			return ((void *)found);
		}
		i++;
	}
	return (NULL);
}
