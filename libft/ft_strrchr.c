/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:43:32 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 18:38:09 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	to_find;
	char			*st;
	char			*last_c;

	to_find = (unsigned char)c;
	st = (char *)s;
	last_c = NULL;
	i = 0;
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
