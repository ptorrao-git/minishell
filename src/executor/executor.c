/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:42:15 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:42:15 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pid(t_executor *exec, t_cmds **cmds)
{
	int		i;
	t_cmds	*temp_cmds;

	i = 0;
	temp_cmds = *cmds;
	while (temp_cmds)
	{
		++i;
		temp_cmds = temp_cmds->next;
	}
	exec->n_process = i;
	if (i == 0)
		return (i);
	exec->pid = (int *)malloc((i + 1) * sizeof(int));
	exec->pid[i] = 0;
	return (i);
}

bool	handle_pipe(t_executor *exec, t_cmds **temp)
{
	int		fd[2];
	int		i;
	t_token	*start;

	i = -1;
	start = NULL;
	while (*temp)
	{
		pipe(fd);
		exec->pid[++i] = fork();
		if (exec->pid[i])
		{
			if (handle_parent(exec, temp, fd))
				return (true);
		}
		else
		{
			if (handle_child(exec, temp, start, fd))
				break ;
			else
				return (false);
		}
	}
	handle_close(exec, fd);
	return (false);
}

bool	builtin(t_executor *exec, t_cmds **cmds)
{
	t_cmds	*temp_cmds;

	temp_cmds = *(cmds);
	if (!handle_redirects(exec, temp_cmds))
		return (false);
	if (!ft_strcmp((temp_cmds)->cmd, "cd"))
		cd(exec->shell, (temp_cmds)->args, exec);
	else if (!ft_strcmp((temp_cmds)->cmd, "pwd"))
		pwd((temp_cmds)->args, exec);
	else if (!ft_strcmp((temp_cmds)->cmd, "echo"))
		echo((temp_cmds)->args, exec);
	else if (!ft_strcmp((temp_cmds)->cmd, "export"))
		export(exec);
	else if (!ft_strcmp((temp_cmds)->cmd, "unset"))
		unset((temp_cmds)->args, exec);
	else if (!ft_strcmp((temp_cmds)->cmd, "env"))
		env(exec->shell, (temp_cmds)->args, exec);
	else if (!ft_strcmp((temp_cmds)->cmd, "exit"))
		exit_builtin(exec->shell->status, exec, (temp_cmds)->args);
	return (true);
}

int	executor(t_executor *exec)
{
	char	*str_path;
	t_cmds	*temp_cmds;

	str_path = NULL;
	temp_cmds = *(exec->cmds);
	if (create_pid(exec, &temp_cmds) == 1 && check_builtin(&temp_cmds))
		return (free(exec->pid), exec->pid = NULL, builtin(exec, &temp_cmds));
	if (handle_pipe(exec, &temp_cmds))
		return (1);
	if (!handle_redirects(exec, temp_cmds))
		return (1);
	if (check_builtin(&temp_cmds))
		builtin(exec, &temp_cmds);
	else
		exec_execve(str_path, exec, temp_cmds);
	return (1);
}

int	exec_execve(char *str_path, t_executor *exec, t_cmds *cmds)
{
	int		exit_status;
	t_cmds	*temp_cmds;

	exit_status = 0;
	temp_cmds = cmds;
	if (!temp_cmds->cmd && exec->is_child)
	{
		free_process(exec);
		exit(0);
	}
	if (ft_strchr((temp_cmds)->cmd, '/') || !ft_strncmp((temp_cmds)->cmd, "./",
			2))
		str_path = ft_strdup((temp_cmds)->cmd);
	else
		str_path = cmd_path(exec, temp_cmds->cmd);
	if (execve(str_path, (temp_cmds)->args, exec->shell->env) == -1)
		exec->shell->status = 127;
	check_global(exec);
	error_check(exec, temp_cmds);
	exit_status = exec->shell->status;
	free(str_path);
	str_path = NULL;
	free_process(exec);
	exit(exit_status);
}
