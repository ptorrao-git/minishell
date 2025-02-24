/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:11:07 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/05/24 18:19:22 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_do_pointer(unsigned long nb)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (nb >= 16)
		count += ft_do_pointer(nb / 16);
	count += ft_putchar(base[nb % 16]);
	return (count);
}

int	ft_pointer(unsigned long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
	{
		count = ft_putstr("(nil)");
		return (count);
	}
	count += ft_putstr("0x");
	count += ft_do_pointer(nb);
	return (count);
}
