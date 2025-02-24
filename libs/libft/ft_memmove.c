/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:29:18 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/04/24 15:59:44 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*t_dst;
	char	*t_src;
	size_t	i;

	if (!src && !dst)
		return (NULL);
	i = -1;
	t_dst = (char *) dst;
	t_src = (char *) src;
	if (t_dst > t_src)
	{
		while (len--)
			t_dst[len] = t_src[len];
	}
	else
	{
		while (++i < len)
			t_dst[i] = t_src[i];
	}
	return (dst);
}
