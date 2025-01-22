/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:28:30 by kruseva           #+#    #+#             */
/*   Updated: 2024/10/17 20:59:55 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

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

static unsigned int	handle_negative(int n, int *is_negative_sign)
{
	unsigned int	new_n;

	if (n < 0)
	{
		*is_negative_sign = 1;
		new_n = -n;
	}
	else
	{
		*is_negative_sign = 0;
		new_n = n;
	}
	return (new_n);
}

char	*ft_itoa_1(int n)
{
	int				is_negative_sign;
	int				decimals_count;
	unsigned int	new_n;
	static char		str[13];
	int				i;

	if (n == -2147483648)
		return ("-2147483648");
	new_n = handle_negative(n, &is_negative_sign);
	decimals_count = count_decimals(new_n);
	if (is_negative_sign)
		decimals_count++;
	str[decimals_count] = '\0';
	i = decimals_count - 1;
	while (i >= 0)
	{
		str[i--] = (new_n % 10) + '0';
		new_n /= 10;
	}
	if (is_negative_sign)
		str[0] = '-';
	return (str);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	*num_ascii;

	num_ascii = ft_itoa_1(n);
	write(fd, num_ascii, ft_strlen(num_ascii));
}
