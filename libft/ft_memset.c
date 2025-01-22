/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:14:07 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 18:25:50 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*newarray;
	char	value;
	size_t	i;

	newarray = s;
	value = (char)c;
	i = 0;
	while (i < n)
	{
		newarray[i] = value;
		i++;
	}
	return (s);
}
