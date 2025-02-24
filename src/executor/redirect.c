/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:42:28 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:42:28 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_dir(char *path)
{
	struct stat	buffer;

	if (stat(path, &buffer) == -1)
		return (0);
	else if (S_ISDIR(buffer.st_mode))
		return (1);
	else if (S_ISREG(buffer.st_mode))
		return (2);
	return (0);
}

bool	check_permission2(t_executor *exec, char *path, int i)
{
	if (i == 1 && access(path, R_OK))
	{
		print_error(" Permission denied\n");
		if (!exec->is_child)
		{
			exec->shell->status = 1;
			return (false);
		}
		free_process(exec);
		exit(1);
	}
	if (i == 2 && access(path, W_OK))
	{
		print_error(" Permission denied\n");
		if (!exec->is_child)
		{
			exec->shell->status = 1;
			return (false);
		}
		free_process(exec);
		exit(1);
	}
	return (true);
}

bool	check_permission(t_executor *exec, char *path, int i)
{
	if (access(path, F_OK))
	{
		print_error(" No such file or directory\n");
		if (!exec->is_child)
		{
			exec->shell->status = 1;
			return (false);
		}
		free_process(exec);
		exit(1);
	}
	if (!check_permission2(exec, path, i))
		return (false);
	if (i == 3 && access(path, X_OK))
	{
		print_error(" Permission denied\n");
		if (!exec->is_child)
		{
			exec->shell->status = 1;
			return (false);
		}
		free_process(exec);
		exit(1);
	}
	return (true);
}

bool	handle_redirects(t_executor *exec, t_cmds *cmds)
{
	int		fd_in;
	int		fd_out;
	t_token	*temp;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	temp = cmds->redir;
	while (temp)
	{
		if (!check_redirection(exec, temp, fd_in, fd_out))
			return (false);
		if (check_is_dir(temp->info) != 2)
		{
			print_error("Path is a directory");
			if (!exec->is_child)
			{
				exec->shell->status = 1;
				return (false);
			}
			free_process(exec);
			exit(2);
		}
		temp = temp->next;
	}
	return (true);
}
