/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:42:07 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/10 22:10:28 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*enum_heredoc(void)
{
	static int	i = -1;
	char		*num;
	char		*file;

	num = ft_itoa(++i);
	file = ft_strjoin(".746D70", num);
	free(num);
	return (file);
}

bool	check_signal(int i)
{
	static int	j = 0;

	if (i == 1)
	{
		j = 1;
		return (j);
	}
	if (j != 0)
		return (j = 0, 1);
	return (0);
}

bool	handle_heredoc(t_cmds *cmds, t_executor *exec)
{
	char	*line;
	char	*eof;
	int		fd;

	eof = ft_strdup(cmds->redir->info);
	free(cmds->redir->info);
	cmds->redir->info = enum_heredoc();
	fd = open(cmds->redir->info, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (false);
	cmds->fd_hd = fd;
	signal(SIGINT, handle_sighd);
	line = readline("> ");
	check_global(exec);
	if (check_signal(0))
		return (free(eof), false);
	while (line && ft_strcmp(line, eof))
	{
		line = heredoc_line(fd, line);
		line = readline("> ");
		check_global(exec);
		if (check_signal(0))
			return (close(fd), free(eof), false);
	}
	return (close(fd), free(eof), true);
}

bool	find_heredoc(t_cmds **cmds, t_executor *exec)
{
	t_cmds	*temp;
	t_token	*original;

	temp = *cmds;
	original = NULL;
	while (temp)
	{
		original = temp->redir;
		while (temp->redir)
		{
			if (temp->redir->type)
				if (temp->redir->type == HERE_DOC)
					if (!handle_heredoc(temp, exec))
						return (false);
			temp->redir = temp->redir->next;
		}
		temp->redir = original;
		temp = temp->next;
	}
	return (true);
}

void	remove_file(void)
{
	static int	j = -1;
	char		*num;
	char		*file;

	num = ft_itoa(++j);
	file = ft_strjoin(".746D70", num);
	while (unlink(file) != -1)
	{
		free(num);
		free(file);
		num = ft_itoa(++j);
		file = ft_strjoin(".746D70", num);
	}
	j--;
	free(num);
	free(file);
}
