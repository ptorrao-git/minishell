/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:43:49 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:43:49 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	realloc_unset(t_executor *exec, int x, int i)
{
	int		j;
	char	**new_env;

	j = 0;
	while (exec->shell->env[++i])
		j++;
	new_env = malloc(sizeof(char *) * (j + 1));
	if (!new_env)
		return (0);
	i = -1;
	j = -1;
	while (exec->shell->env[++i])
	{
		if (i == x)
			++i;
		if (exec->shell->env[i])
			new_env[++j] = ft_strdup(exec->shell->env[i]);
		if (!exec->shell->env[i])
			break ;
	}
	new_env[++j] = NULL;
	free_mtr(exec->shell->env);
	exec->shell->env = new_env;
	return (1);
}

int	unset(char **mtr, t_executor *exec)
{
	int	i;
	int	j;

	i = 0;
	if (mtr[1] && mtr[1][0] == '-')
	{
		w_error("unset: can not receive arguments or options"
			" (imposed by subject)\n");
		return (set_exit_status(exec->shell, 1), 1);
	}
	while (mtr[++i])
	{
		j = -1;
		while (exec->shell->env[++j])
		{
			if (ft_strncmp(exec->shell->env[j], mtr[i], ft_strlen(mtr[i])) == 0)
			{
				if (!realloc_unset(exec, j, -1))
					return (set_exit_status(exec->shell, 1), 0);
				break ;
			}
		}
	}
	return (set_exit_status(exec->shell, 0), 1);
}
