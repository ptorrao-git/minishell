/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:07:18 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/04/22 19:19:39 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*t_s1;
	const char	*t_s2;

	i = 0;
	t_s1 = s1;
	t_s2 = s2;
	if (n == 0)
		return (0);
	while ((t_s1[i] == t_s2[i]) && (i < n - 1))
		i++;
	return ((unsigned char) t_s1[i] - (unsigned char) t_s2[i]);
}
