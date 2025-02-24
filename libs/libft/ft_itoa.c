/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:10:35 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/05/02 15:21:01 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	t_n;

	t_n = n;
	i = ft_size(n);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (t_n < 0)
	{
		str[0] = '-';
		t_n *= -1;
	}
	else if (t_n == 0)
		str[0] = '0';
	while (t_n != 0)
	{
		str[--i] = (t_n % 10) + 48;
		t_n /= 10;
	}
	return (str);
}
