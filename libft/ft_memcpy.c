/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:54:36 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 18:25:19 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*sr;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (char *)dest;
	sr = (const char *)src;
	while (i < n)
	{
		d[i] = sr[i];
		i++;
	}
	return (dest);
}
