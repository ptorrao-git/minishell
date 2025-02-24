/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:06:45 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/08/05 19:38:22 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_gnl_strchr(char *s, int c)
{
	while (*s != '\0' && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *) s);
	else
		return (NULL);
}

char	*ft_gnl_strndup(char *s, int len)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_gnl_strclen(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while ((str[i] && str[i] != c))
		i++;
	return (i);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*newstring;
	int		i;
	int		j;
	int		size;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	size = ft_gnl_strclen(s1, '\0') + ft_gnl_strclen(s2, '\0');
	newstring = malloc(sizeof(char *) * (size + 1));
	if (!newstring)
		return (0);
	i = -1;
	j = 0;
	while ((i < size) && (s1[++i]))
		newstring[i] = s1[i];
	while ((i < size) && (s2[j]))
		newstring[i++] = s2[j++];
	newstring[i] = '\0';
	if (s1)
		free (s1);
	return (newstring);
}
