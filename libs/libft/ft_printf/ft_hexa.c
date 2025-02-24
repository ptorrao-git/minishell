/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:28:44 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/05/24 18:37:09 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa(unsigned int nb, const char c)
{
	int		count;
	char	*l_base;
	char	*u_base;

	count = 0;
	l_base = "0123456789abcdef";
	u_base = "0123456789ABCDEF";
	if (nb >= 16)
		count += ft_hexa(nb / 16, c);
	if (c == 'x')
		count += ft_putchar(l_base[nb % 16]);
	if (c == 'X')
		count += ft_putchar(u_base[nb % 16]);
	return (count);
}
