/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:37:08 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/12/05 18:46:08 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_i;
	size_t	s2_i;
	char	*s_s;

	if (!s1 || !s2)
		return (NULL);
	s1_i = ft_strlen(s1);
	s2_i = ft_strlen(s2);
	s_s = malloc((s1_i + s2_i + 1) * (sizeof(char)));
	if (!s_s)
		return (NULL);
	i = 0;
	while (i < s1_i && s1)
	{
		s_s[i] = s1[i];
		i++;
	}
	s1_i = 0;
	while (s1_i < s2_i && s2)
		s_s[i++] = s2[s1_i++];
	s_s[i] = '\0';
	return (s_s);
}

char	*ft_strjoin_free(char *s1, char const *s2, bool to_free)
{
	size_t	i;
	size_t	s1_i;
	size_t	s2_i;
	char	*s_s;

	if (!s1 || !s2)
		return (NULL);
	s1_i = ft_strlen(s1);
	s2_i = ft_strlen(s2);
	s_s = malloc((s1_i + s2_i + 1) * (sizeof(char)));
	if (!s_s)
		return (NULL);
	i = 0;
	while (i < s1_i && s1)
	{
		s_s[i] = s1[i];
		i++;
	}
	s1_i = 0;
	while (s1_i < s2_i && s2)
		s_s[i++] = s2[s1_i++];
	s_s[i] = '\0';
	if (to_free)
		free(s1);
	return (s_s);
}
