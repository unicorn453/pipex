/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:43:32 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/25 18:09:30 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	to_find;
	char			*st;
	char			*last_c;

	to_find = (unsigned char)c;
	st = (char *)s;
	last_c = NULL;
	while (*st != '\0')
	{
		if (to_find == *st)
		{
			last_c = st;
		}
		st++;
	}
	if (to_find == '\0')
	{
		return (st);
	}
	return (last_c);
}
