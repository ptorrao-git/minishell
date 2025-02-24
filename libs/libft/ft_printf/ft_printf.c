/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:39:04 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/07/10 18:07:33 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	ft_convertions(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar((char)va_arg(args, int));
	else if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (c == 'i' || c == 'd')
		count += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		count += ft_uputnbr(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		count += ft_hexa(va_arg(args, unsigned int), c);
	else if (c == 'p')
		count += ft_pointer(va_arg(args, unsigned long));
	else if (c == '%')
		count += ft_putchar(c);
	return (count);
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, string);
	if (!string)
		return (0);
	while (*string)
	{
		if (*string == '%')
		{
			string++;
			count += ft_convertions(*string, args);
		}
		else
			count += ft_putchar(*string);
		string++;
	}
	va_end(args);
	return (count);
}
