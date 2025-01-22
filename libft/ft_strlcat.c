/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:05:24 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 20:46:18 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lensrc;
	size_t	lendest;
	size_t	totallen;
	size_t	leftspace;

	lensrc = ft_strlen(src);
	lendest = ft_strlen(dst);
	totallen = lendest + lensrc;
	if (size == 0)
		return (lensrc);
	if (size <= lendest)
		return (size + lensrc);
	leftspace = size - lendest - 1;
	if (leftspace > 0)
	{
		if (leftspace > lensrc)
			leftspace = lensrc;
		ft_memcpy(dst + lendest, src, leftspace);
		dst[lendest + leftspace] = '\0';
	}
	else
		dst[lendest] = '\0';
	return (totallen);
}
