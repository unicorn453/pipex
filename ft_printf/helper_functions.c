/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:26:18 by kruseva           #+#    #+#             */
/*   Updated: 2024/11/14 15:37:37 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	count;
	int	ret;

	count = 0;
	if (!s)
		s = "(null)";
	while (*s)
	{
		ret = write(1, s, 1);
		if (ret == -1)
			return (-1);
		s++;
		count++;
	}
	return (count);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	get_hex_length_ptr(unsigned long long num)
{
	int	length;

	length = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 16;
		length++;
	}
	return (length);
}

void	convert_to_hex_ptr(char *buffer, unsigned long long num, int isUpper)
{
	int	index;
	int	remainder;

	index = get_hex_length_ptr(num) - 1;
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

int	ft_putptr(void *ptr)
{
	unsigned long long	num;
	char				buffer[18];
	int					check;
	int					length;

	num = (unsigned long long)ptr;
	check = write(1, "0x", 2);
	if (check == -1)
	{
		return (-1);
	}
	if (num == 0)
	{
		check = write(1, "0", 1);
		if (check == -1)
			return (-1);
		return (3);
	}
	length = get_hex_length_ptr(num);
	convert_to_hex_ptr(buffer, num, 0);
	check = write(1, buffer, length);
	if (check == -1)
		return (-1);
	return (length + 2);
}
