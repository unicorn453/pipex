/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:11:38 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 18:35:17 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	to_copy;

	len = ft_strlen(src);
	if (size == 0)
	{
		return (len);
	}
	if (size > 0)
	{
		if (len < size - 1)
		{
			to_copy = len;
		}
		else
		{
			to_copy = size - 1;
		}
		ft_memcpy(dst, src, to_copy);
		dst[to_copy] = '\0';
	}
	return (len);
}
