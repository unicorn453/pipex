/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:58:10 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 18:33:03 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	size;
	size_t	dfifj;
	char	*ptr;

	size = ft_strlen(s1);
	ptr = malloc(size + 1);
	if (!ptr)
		return (NULL);
	dfifj = ft_strlcpy(ptr, s1, size + 1);
	if (!ptr)
	{
		return (NULL);
	}
	return (ptr);
}
