/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:25:35 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/10 21:15:20 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_close(t_executor *exec, int *fd)
{
	dup2(exec->fd_out, STDOUT_FILENO);
	close(exec->fd_out);
	close(fd[0]);
	close(fd[1]);
}

bool	handle_child(t_executor *exec, t_cmds **temp, t_token *start, int *fd)
{
	exec->is_child = true;
	if (!(*temp)->next)
		return (true);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if ((*temp)->next && (*temp)->next->redir)
		start = (*temp)->next->redir;
	while ((*temp)->next && (*temp)->next->redir)
	{
		if ((*temp)->next->redir->type == RED_IN
			|| (*temp)->next->redir->type == HERE_DOC)
			return ((*temp)->next->redir = start, false);
		(*temp)->next->redir = (*temp)->next->redir->next;
	}
	if (start)
		(*temp)->next->redir = start;
	close(fd[0]);
	return (false);
}

bool	check_builtin(t_cmds **cmds)
{
	t_cmds	*temp_cmds;

	temp_cmds = *(cmds);
	if (!temp_cmds->cmd)
		return (false);
	if (!ft_strcmp((temp_cmds)->cmd, "cd"))
		return (true);
	else if (!ft_strcmp((temp_cmds)->cmd, "pwd"))
		return (true);
	else if (!ft_strcmp((temp_cmds)->cmd, "echo"))
		return (true);
	else if (!ft_strcmp((temp_cmds)->cmd, "export"))
		return (true);
	else if (!ft_strcmp((temp_cmds)->cmd, "unset"))
		return (true);
	else if (!ft_strcmp((temp_cmds)->cmd, "env"))
		return (true);
	else if (!ft_strcmp((temp_cmds)->cmd, "exit"))
		return (true);
	return (false);
}

bool	handle_parent(t_executor *exec, t_cmds **temp, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (ft_strcmp((*exec->cmds)->cmd, "./minishell") == 0)
		signal(SIGINT, SIG_IGN);
	else
		signal(SIGINT, exec_sig);
	if (!(*temp)->next)
		return (dup2(exec->fd_in, STDIN_FILENO), true);
	*temp = (*temp)->next;
	return (false);
}
