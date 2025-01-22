/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:10:11 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 18:37:49 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*start;
	size_t		i;
	size_t		j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		start = &haystack[i];
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] != '\0' && (i
				+ j) < len)
		{
			if (haystack[i] == '\0')
				return (NULL);
			j++;
			if (needle[j] == '\0')
				return ((char *)start);
		}
		i++;
	}
	return (NULL);
}
