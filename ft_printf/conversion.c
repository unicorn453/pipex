/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:16:57 by kruseva           #+#    #+#             */
/*   Updated: 2024/11/14 16:39:46 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_conversion(const char *format, va_list args)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	length += cases(format[i + 1], args);
	return (length);
}

int	handle_char(char c, va_list args)
{
	char	ch;

	if (c == 'c')
	{
		ch = (char)va_arg(args, int);
		if (write(1, &ch, 1) == -1)
			return (-1);
		return (1);
	}
	else if (c == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		return (1);
	}
	return (-1);
}

int	handle_string_pointer(char c, va_list args)
{
	char	*str;
	void	*ptr;

	if (c == 's')
	{
		str = va_arg(args, char *);
		return (ft_putstr(str));
	}
	else if (c == 'p')
	{
		ptr = va_arg(args, void *);
		return (ft_putptr(ptr));
	}
	return (-1);
}

int	handle_numbers(char c, va_list args)
{
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_putsmallhex(va_arg(args, unsigned int)));
	else if (c == 'X')
		return (ft_puthex(va_arg(args, unsigned int)));
	return (-1);
}

int	cases(char c, va_list args)
{
	int	result;

	result = handle_char(c, args);
	if (result != -1)
		return (result);
	result = handle_string_pointer(c, args);
	if (result != -1)
		return (result);
	result = handle_numbers(c, args);
	if (result != -1)
		return (result);
	return (-1);
}
