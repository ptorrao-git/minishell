/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:36:29 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/04/22 17:18:20 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	big_i;

	i = 0;
	big_i = 0;
	if (*little == '\0' || big == little)
		return ((char *) big);
	while (big_i < len && big[big_i] != '\0')
	{
		if (big[big_i] == little[i])
		{
			i++;
			big_i++;
		}
		else
		{
			big_i = big_i - i + 1;
			i = 0;
		}
		if (little[i] == '\0')
			return ((char *) big + big_i - i);
	}
	return (NULL);
}
