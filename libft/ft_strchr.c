/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:51:40 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 18:32:46 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	to_find;
	char			*st;

	to_find = (unsigned char)c;
	st = (char *)s;
	i = 0;
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
