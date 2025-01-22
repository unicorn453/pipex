/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexadecimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:17:35 by kruseva           #+#    #+#             */
/*   Updated: 2024/11/14 15:25:14 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	convert_to_hex(char *buffer, unsigned int num, int isUpper)
{
	int	index;
	int	remainder;

	index = get_hex_length(num) - 1;
	while (num > 0)
	{
		remainder = num % 16;
		if (remainder < 10)
			buffer[index--] = '0' + remainder;
		else
		{
			if (isUpper)
				buffer[index--] = 'A' + (remainder - 10);
			else
				buffer[index--] = 'a' + (remainder - 10);
		}
		num /= 16;
	}
}

int	get_hex_length(unsigned int num)
{
	unsigned int	length;

	length = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 16;
		length++;
	}
	return ((int)length);
}

int	ft_putsmallhex(unsigned int num)
{
	char	buffer[20];
	int		length;
	int		check;

	length = get_hex_length(num);
	if (num == 0)
	{
		check = write(1, "0", 1);
		if (check == -1)
			return (-1);
		return (1);
	}
	convert_to_hex(buffer, num, 0);
	check = write(1, buffer, length);
	if (check == -1)
		return (-1);
	return (length);
}

int	ft_puthex(unsigned int num)
{
	char	buffer[20];
	int		length;
	int		check;

	length = get_hex_length(num);
	if (num == 0)
	{
		check = write(1, "0", 1);
		if (check == -1)
			return (-1);
		return (1);
	}
	convert_to_hex(buffer, num, 1);
	check = write(1, buffer, length);
	if (check == -1)
		return (-1);
	return (length);
}
