/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:38:21 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/05/24 16:28:49 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nb)
{
	long	i;
	int		count;

	count = 0;
	i = nb;
	if (i < 0)
	{
		count += ft_putchar('-');
		i *= -1;
	}
	if (i >= 10)
		count += ft_putnbr(i / 10);
	count += ft_putchar(i % 10 + '0');
	return (count);
}
