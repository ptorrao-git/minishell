/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:49 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:49 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd(t_executor *exec)
{
	if (exec->fd_in)
		close(exec->fd_in);
	if (exec->fd_out)
		close(exec->fd_out);
}

void	free_d(t_executor *exec)
{
	if (exec->shell->env)
	{
		free_mtr(exec->shell->env);
		exec->shell->env = NULL;
	}
	if (exec->cmds)
	{
		free(exec->cmds);
		exec->cmds = NULL;
	}
	if (exec->shell)
	{
		free(exec->shell);
		exec->shell = NULL;
	}
	if (exec->token)
	{
		free(exec->token);
		exec->token = NULL;
	}
	free_fd(exec);
}

void	free_all(t_executor *exec)
{
	if (exec->shell->line)
	{
		free(exec->shell->line);
		exec->shell->line = NULL;
	}
	ft_free_cmds(*exec->cmds);
	if (exec->pid)
	{
		free(exec->pid);
		exec->pid = NULL;
	}
}

void	free_process(t_executor *exec)
{
	free_all(exec);
	free_d(exec);
	if (exec)
	{
		free(exec);
		exec = NULL;
	}
}
