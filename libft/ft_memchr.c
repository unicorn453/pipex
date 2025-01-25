/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:43:10 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/25 18:12:57 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	to_find;
	char	*str;
	char	*found;

	to_find = c;
	str = (char *)s;
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
