/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:52:51 by kruseva           #+#    #+#             */
/*   Updated: 2024/11/14 15:44:24 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_conversion(const char *format, va_list args, int *i)
{
	int	conversion_count;

	if (format[*i + 1] == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		(*i)++;
		return (1);
	}
	else
	{
		conversion_count = check_conversion(&format[*i], args);
		if (conversion_count == -1)
			return (-1);
		(*i)++;
		return (conversion_count);
	}
}

int	process_format(const char *format, va_list args)
{
	int	count;
	int	i;
	int	conversion_count;

	count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%' && format[i] != '\0')
		{
			if (write(1, &format[i], 1) == -1)
				return (-1);
			count++;
		}
		else
		{
			conversion_count = handle_conversion(format, args, &i);
			if (conversion_count == -1)
				return (-1);
			count += conversion_count;
		}
		i++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	count = process_format(format, args);
	va_end(args);
	return (count);
}
