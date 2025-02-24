/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:00:00 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/12/05 18:54:06 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	s_i;
	char	*new_s;

	i = 0;
	s_i = ft_strlen(s);
	new_s = (char *)malloc(sizeof(char) * (s_i + 1));
	if (!new_s)
		return (NULL);
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*new_s;

	i = 0;
	new_s = (char *)malloc(sizeof(char) * (n + 1));
	if (!new_s)
		return (NULL);
	while (s[i] && i < n)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
