/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:18:11 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/02/06 18:28:01 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_append_loop(t_executor *exec, t_export *export)
{
	int	i;

	i = -1;
	while (exec->shell->env[++i])
	{
		if (compare_result(export, export->arg_left, exec->shell->env[i]) == 0)
		{
			if (exec->shell->env[i][ft_strlen(export->arg_left) - 1] == '=')
			{
				exec->shell->env[i] = ft_strjoin_free(exec->shell->env[i],
						export->arg_right, true);
				break ;
			}
			else
			{
				exec->shell->env[i] = ft_strjoin_free(
						ft_strjoin_free(exec->shell->env[i],
							"=", true), export->arg_right, true);
				break ;
			}
		}
	}
}

void	execute_append(t_export *export, t_executor *exec)
{
	if (!export->new_entry)
		execute_append_loop(exec, export);
	else
		make_new_entry(export, exec);
}

bool	make_new_entry(t_export *export, t_executor *exec)
{
	char	*temp_arg_left;

	temp_arg_left = NULL;
	exec->shell->env = realloc_env(exec->shell->env);
	if (!exec->shell->env)
		return (free(temp_arg_left), false);
	if (export->append)
	{
		temp_arg_left = ft_strndup(export->arg_left, ft_strlen(export->arg_left)
				- 1);
		exec->shell->env[env_len(exec->shell->env)] = ft_strjoin_free(
				ft_strjoin_free(temp_arg_left, "=", true),
				export->arg_right, true);
	}
	else
	{
		if (export->arg_equals)
			exec->shell->env[env_len(exec->shell->env)] = ft_strjoin_free(
					ft_strjoin(export->arg_left, "="), export->arg_right, true);
		else
			exec->shell->env[env_len(exec->shell->env)] = ft_strdup(
					export->arg_left);
	}
	return (true);
}

bool	replace_entry(t_export *export, t_executor *exec)
{
	int	i;

	i = -1;
	while (exec->shell->env[++i])
	{
		if (export->arg_equals)
		{
			if (ft_strncmp(export->arg_left, exec->shell->env[i],
					ft_strlen(export->arg_left)) == 0)
			{
				free(exec->shell->env[i]);
				exec->shell->env[i] = ft_strjoin_free(ft_strjoin(
							export->arg_left, "="), export->arg_right, true);
				break ;
			}
		}
		else
			break ;
	}
	return (true);
}

bool	execute_export(t_export *export, t_executor *exec)
{
	if (export->do_nothing)
		return (false);
	if (export->append)
		return (execute_append(export, exec), true);
	else
	{
		if (export->new_entry)
			return (make_new_entry(export, exec), true);
		else
			return (replace_entry(export, exec), true);
	}
	return (true);
}
