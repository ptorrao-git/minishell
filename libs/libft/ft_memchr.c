/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:20:46 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/07/29 16:43:12 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*t_s;

	i = 0;
	t_s = s;
	if (n == 0)
		return (0);
	while (i < n - 1 && t_s[i] != (char)c)
		i++;
	if (t_s[i] == (char)c)
		return ((char *) t_s + i);
	else
		return (NULL);
}
