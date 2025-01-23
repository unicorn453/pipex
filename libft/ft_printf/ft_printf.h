/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:16:28 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/19 23:23:40 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		ft_printf(const char *format, ...);
void	convert_to_hex(char *buffer, unsigned int num, int isUpper);
int		cases(char c, va_list args);
int		ft_putstr(char *s);
size_t	ft_strlen(const char *str);
int		ft_putnbr(int n);
int		check_conversion(const char *format, va_list args);
int		ft_putsmallhex(unsigned int num);
int		ft_puthex(unsigned int num);
int		ft_putptr(void *ptr);
int		get_hex_length(unsigned int num);
int		ft_putunbr(unsigned int n);
