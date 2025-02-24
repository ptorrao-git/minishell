/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:06:42 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/08/01 17:32:25 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*set_stash(char *stash)
{
	char	*temp;

	temp = ft_gnl_strndup(stash + ft_gnl_strclen(stash, '\n')
			+ 1, ft_gnl_strclen(stash, '\0') - ft_gnl_strclen(stash, '\n'));
	free (stash);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*free_data(char *buf, char *stash)
{
	free(buf);
	free(stash);
	return (NULL);
}

char	*fill_stash(int fd, char *stash)
{
	char		*buf;
	ssize_t		size;

	size = BUFFER_SIZE;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	*buf = 0;
	while (!ft_gnl_strchr(buf, '\n') && size != 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
			return (free_data(buf, stash));
		buf[size] = '\0';
		stash = ft_gnl_strjoin(stash, buf);
	}
	if (*stash == '\0' || size == -1)
		return (free_data(buf, stash));
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[MAX_FD];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = NULL;
	stash[fd] = fill_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_gnl_strndup(stash[fd], ft_gnl_strclen(stash[fd], '\n') + 1);
	if (!line)
		return (NULL);
	stash[fd] = set_stash(stash[fd]);
	if (!stash[fd])
		free(stash[fd]);
	return (line);
}
