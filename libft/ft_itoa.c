/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:23:09 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 20:41:42 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*itoa_helper(int n, int decimals_count)
{
	char	*str;
	int		i;

	str = (char *)malloc(decimals_count + 1);
	if (!str)
		return (NULL);
	str[decimals_count] = '\0';
	i = decimals_count - 1;
	while (i >= 0)
	{
		str[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

static int	count_decimals(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	handle_negative(int *n)
{
	if (*n < 0)
	{
		*n = -*n;
		return (1);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	int		is_negative_sign;
	int		decimals_count;
	int		new_n;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	is_negative_sign = handle_negative(&n);
	new_n = n;
	decimals_count = count_decimals(new_n);
	if (is_negative_sign)
		decimals_count++;
	str = itoa_helper(n, decimals_count);
	if (!str)
		return (NULL);
	if (is_negative_sign)
		str[0] = '-';
	return (str);
}
