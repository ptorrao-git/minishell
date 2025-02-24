/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:22:29 by ddias-fe          #+#    #+#             */
/*   Updated: 2024/11/30 18:54:48 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinpath(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_i;
	size_t	s2_i;
	char	*s_s;

	if (!s1 || !s2)
		return (NULL);
	s1_i = ft_strlen(s1);
	s2_i = ft_strlen(s2);
	s_s = malloc((s1_i + s2_i + 2) * (sizeof(char)));
	if (!s_s)
		return (NULL);
	i = 0;
	while (i < s1_i && s1)
	{
		s_s[i] = s1[i];
		i++;
	}
	s_s[i++] = '/';
	s1_i = 0;
	while (s1_i < s2_i && s2)
		s_s[i++] = s2[s1_i++];
	s_s[i] = '\0';
	return (s_s);
}
