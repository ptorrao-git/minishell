/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:44:16 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/05/03 15:45:49 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_in_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	is;
	size_t	s1_i;
	char	*s_s1;

	if (!s1)
		return (NULL);
	s1_i = ft_strlen(s1);
	is = 0;
	i = 0;
	while (s1[is] && ft_in_set(s1[is], set))
		is++;
	while (s1_i > is && ft_in_set(s1[s1_i - 1], set))
		s1_i--;
	s_s1 = (char *)malloc((s1_i - is + 1) * (sizeof(char)));
	if (!s_s1)
		return (NULL);
	while (s1_i > is)
		s_s1[i++] = s1[is++];
	s_s1[i] = '\0';
	return (s_s1);
}
