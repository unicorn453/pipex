/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:51:40 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/25 18:09:06 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	to_find;
	char			*st;

	to_find = (unsigned char)c;
	st = (char *)s;
	while (*st != '\0')
	{
		if (to_find == *st)
		{
			return (st);
		}
		st++;
	}
	if (to_find == '\0')
	{
		return (st);
	}
	return (NULL);
}
