/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:42:55 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:42:55 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_the_child(t_executor *exec)
{
	free_process(exec);
	exit(1);
}

bool	env(t_shell *shell, char **mtr, t_executor *exec)
{
	int	i;

	i = -1;
	if (mtr[1])
	{
		w_error("env: can not receive arguments or "
			"options (imposed by subject)\n");
		set_exit_status(exec->shell, 1);
		if (exec->is_child)
			exit_the_child(exec);
		return (1);
	}
	while (shell->env[++i])
	{
		if (ft_strchr(shell->env[i], '='))
			ft_printf("%s\n", shell->env[i]);
	}
	if (exec->is_child)
	{
		free_process(exec);
		exit(0);
	}
	return (set_exit_status(exec->shell, 0), true);
}
