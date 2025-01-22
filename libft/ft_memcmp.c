/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:58:54 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 18:24:47 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*comp1;
	unsigned char	*comp2;

	comp1 = (unsigned char *)s1;
	comp2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (!(comp1[i] == comp2[i]))
		{
			if (comp1[i] > comp2[i])
			{
				return (comp1[i] - comp2[i]);
			}
			if (comp1[i] < comp2[i])
			{
				return (comp1[i] - comp2[i]);
			}
		}
		i++;
	}
	return (0);
}
