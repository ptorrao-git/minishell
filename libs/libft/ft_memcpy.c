/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:20:13 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/04/24 15:34:58 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*t_dst;
	unsigned char	*t_src;

	if (!src && !dst)
		return (NULL);
	t_dst = (unsigned char *) dst;
	t_src = (unsigned char *) src;
	while (n > 0)
	{
		*(t_dst++) = *(t_src++);
		n--;
	}
	return (dst);
}
