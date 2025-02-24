/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:25:25 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/02/06 14:25:25 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_child(t_executor *exec, int exit_code, t_export *export)
{
	free_process(exec);
	free_export_args(export);
	free_export(export);
	exit(exit_code);
}

static void	content_loop(t_export *export, t_cmds *cmd, t_executor *exec, int i)
{
	if (parse_export(cmd->args[i], export))
	{
		if (!execute_export(export, exec))
		{
			if (exec->is_child)
				exit_child(exec, 1, export);
			set_exit_status(exec->shell, 1);
			free_export_args(export);
		}
		else
		{
			if (exec->is_child)
				exit_child(exec, 0, export);
			free_export_args(export);
		}
	}
	else
	{
		if (exec->is_child)
			exit_child(exec, 1, export);
		set_exit_status(exec->shell, 1);
		free_export_args(export);
	}
}

static int	export_with_args(t_export *export, t_cmds *cmd, t_executor *exec)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
	{
		if (i > 1)
		{
			export = malloc(sizeof(t_export));
			if (!export)
				return (0);
			export = init_export(export, exec);
		}
		content_loop(export, cmd, exec, i);
		free_export(export);
	}
	return (1);
}

int	export(t_executor *exec)
{
	t_cmds		*cmd;
	t_export	*export;

	cmd = *(exec->cmds);
	export = malloc(sizeof(t_export));
	if (!export)
		return (0);
	export = init_export(export, exec);
	if (cmd->args[0] && !cmd->args[1])
	{
		print_export(export);
		if (exec->is_child)
			exit_child(exec, 0, export);
		return (set_exit_status(exec->shell, 0), free_export(export), 1);
	}
	else if (cmd->args[1])
		return (export_with_args(export, cmd, exec));
	return (set_exit_status(exec->shell, 0), 1);
}

void	print_export(t_export *export)
{
	int	i;

	bubblesort(export);
	i = -1;
	while (export->key_left[++i])
	{
		ft_printf("declare -x %s", export->key_left[i]);
		if (export->key_right[i])
			ft_printf("=\"%s\"\n", export->key_right[i]);
		else
			ft_printf("\n");
	}
}
