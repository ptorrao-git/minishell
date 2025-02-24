/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:24:25 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/05/03 12:35:17 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_i;
	size_t	dst_i;

	if (size == 0)
		return (ft_strlen(src) + size);
	src_i = ft_strlen(src);
	dst_i = ft_strlen(dst);
	if (dst_i >= size)
		return (src_i + size);
	i = 0;
	while (((i + dst_i) < size - 1) && src[i])
	{
		dst[dst_i + i] = src[i];
		i++;
	}
	dst[dst_i + i] = '\0';
	return (src_i + dst_i);
}
