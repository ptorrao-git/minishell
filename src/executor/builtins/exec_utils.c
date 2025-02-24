/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:43:03 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:43:03 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getenvp(char **envp, char *var)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == var[j] && envp[i][j] != '=')
			j++;
		if (envp[i][j] == '=')
			return (envp[i] + j + 1);
		i++;
	}
	return (NULL);
}

void	wait_pid(t_executor *exec)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!exec->pid)
		return ;
	while (exec->pid[i] != 0)
	{
		waitpid(exec->pid[i++], &j, 0);
		exec->shell->status = WEXITSTATUS(j);
	}
	free(exec->pid);
	exec->n_process = 0;
	exec->pid = NULL;
}

void	exit_exec(t_executor *exec, t_cmds *cmds)
{
	if (ft_strchr(cmds->cmd, '/') || !ft_strncmp(cmds->cmd, "./", 2))
	{
		if (check_is_dir(cmds->cmd) == 1)
		{
			print_error(cmds->cmd);
			print_error(": Is a directory\n");
			exec->shell->status = 126;
		}
		else
		{
			print_error(cmds->cmd);
			print_error(": Permission denied\n");
			exec->shell->status = 126;
		}
	}
	else
	{
		print_error(cmds->cmd);
		print_error(": command not found\n");
	}
}

void	exit_exec2(t_executor *exec, t_cmds *cmds)
{
	if (ft_strchr(cmds->cmd, '/') || !ft_strncmp(cmds->cmd, "./", 2))
	{
		if (check_is_dir(cmds->cmd) == 1)
		{
			print_error(cmds->cmd);
			print_error(": Is a directory\n");
			exec->shell->status = 126;
		}
		else
		{
			print_error(cmds->cmd);
			print_error(": No such file or directory\n");
			exec->shell->status = 127;
		}
	}
	else
	{
		print_error(cmds->cmd);
		print_error(": command not found\n");
	}
}

void	error_check(t_executor *exec, t_cmds *cmds)
{
	if (errno == EACCES)
		exit_exec(exec, cmds);
	else if (errno == ENOENT)
		exit_exec2(exec, cmds);
}
