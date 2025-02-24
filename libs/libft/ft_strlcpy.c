/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:28:49 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/04/17 16:49:31 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_i;

	src_i = 0;
	i = 0;
	while (src[src_i])
		src_i++;
	if (size == 0)
		return (src_i);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = '\0';
	return (src_i);
}

/* int	main(void)
{
	char	dest[15];
	printf("%zu\n", ft_strlcpy(dest, "lorem ipsum dolor sit amet", 0));
	printf("%s\n", dest);
	printf("%zu\n", strlcpy(dest, "lorem ipsum dolor sit amet", 0));
	printf("%s\n", dest);
	return (0);
} */