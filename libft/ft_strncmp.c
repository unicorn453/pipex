/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:09:48 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/25 18:12:19 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_non_ascii(unsigned char c1, unsigned char c2)
{
	if (c1 > 127 || c2 > 127)
		return (1);
	return (0);
}

static int	compare_chars(unsigned char c1, unsigned char c2)
{
	if (c1 != c2)
	{
		if (c1 > c2)
			return (c1 - c2);
		else
			return (c1 - c2);
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*comp1;
	unsigned char	*comp2;

	comp1 = (unsigned char *)s1;
	comp2 = (unsigned char *)s2;
	i = 0;
	while ((comp1[i] != '\0' || comp2[i] != '\0') && (i < n))
	{
		if (is_non_ascii(comp1[i], comp2[i]))
			return (-1);
		if (compare_chars(comp1[i], comp2[i]) != 0)
			return (compare_chars(comp1[i], comp2[i]));
		i++;
	}
	return (0);
}
