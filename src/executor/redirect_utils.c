/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:01:25 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/10 19:28:25 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_red_out(t_executor *exec, t_token *temp, int fd_out)
{
	fd_out = open(temp->info, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (!check_permission(exec, temp->info, 2))
		return (false);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (true);
}

bool	check_red_in(t_executor *exec, t_token *temp, int fd_in)
{
	fd_in = open(temp->info, O_RDWR, 0777);
	if (!check_permission(exec, temp->info, 1))
		return (false);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (true);
}

bool	check_if_append(t_executor *exec, t_token *temp, int fd_out)
{
	fd_out = open(temp->info, O_APPEND | O_CREAT | O_RDWR, 0777);
	if (!check_permission(exec, temp->info, 2))
		return (false);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (true);
}

void	check_here_doc(t_token *temp, int fd_in)
{
	fd_in = open(temp->info, O_RDONLY, 0777);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

bool	check_redirection(t_executor *exec, t_token *temp, int fin, int fout)
{
	if (temp->type == RED_OUT)
	{
		if (!check_red_out(exec, temp, fout))
			return (false);
	}
	else if (temp->type == RED_IN)
	{
		if (!check_red_in(exec, temp, fin))
			return (false);
	}
	else if (temp->type == APPEND)
	{
		if (!check_if_append(exec, temp, fout))
			return (false);
	}
	else if (temp->type == HERE_DOC)
		check_here_doc(temp, fin);
	return (true);
}
