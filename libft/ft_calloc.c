/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:11:09 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 19:55:11 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (count == 0 || size == 0)
	{
		arr = malloc(0);
		if (!arr)
			return (NULL);
		ft_memset(arr, 0, 1);
		return (arr);
	}
	if (!count || !size)
		return (NULL);
	arr = malloc(count * size);
	if (!arr)
		return (NULL);
	ft_memset(arr, 0, count * size);
	return (arr);
}
