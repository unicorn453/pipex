/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:31:07 by kruseva           #+#    #+#             */
/*   Updated: 2024/11/14 16:40:21 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_decimals(unsigned int n)
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

char	*ft_itoa_1(unsigned int n)
{
	int			decimals_count;
	static char	str[13];
	int			i;

	decimals_count = count_decimals(n);
	str[decimals_count] = '\0';
	i = decimals_count - 1;
	while (i >= 0)
	{
		str[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

int	ft_putnbr(int n)
{
	char	*num_ascii;
	int		count;
	int		check;

	count = 0;
	if (n == -2147483648)
	{
		check = write(1, "-2147483648", 11);
		if (check == -1)
			return (-1);
		return (11);
	}
	if (n < 0)
	{
		check = write(1, "-", 1);
		if (check == -1)
			return (-1);
		n = -n;
		count++;
	}
	num_ascii = ft_itoa_1((unsigned int)n);
	check = write(1, num_ascii, ft_strlen(num_ascii));
	if (check == -1)
		return (-1);
	return (count + ft_strlen(num_ascii));
}

int	ft_putunbr(unsigned int n)
{
	char	*num_ascii;
	int		count;
	int		check;

	count = 0;
	num_ascii = ft_itoa_1(n);
	check = write(1, num_ascii, ft_strlen(num_ascii));
	if (check == -1)
		return (-1);
	return (count + ft_strlen(num_ascii));
}
