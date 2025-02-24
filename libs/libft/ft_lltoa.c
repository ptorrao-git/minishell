/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:41:31 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/06 15:00:43 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_lsize(long long n)
{
	long long	i;

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

char	*ft_lltoa(long long n)
{
	long long	i;
	char		*str;
	long long	t_n;

	t_n = n;
	i = ft_lsize(n);
	if (n == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
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
	while (i > 0 && t_n != 0)
	{
		str[--i] = (t_n % 10) + 48;
		t_n /= 10;
	}
	return (str);
}
