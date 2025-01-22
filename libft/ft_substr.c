/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 23:29:54 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 18:39:03 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	unsigned int	len_str;

	len_str = ft_strlen(s);
	if (start >= len_str)
	{
		return (ft_strdup(""));
	}
	if (len > len_str - start)
		len = len_str - start;
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, &s[start], len + 1);
	return (new_str);
}
