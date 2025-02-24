/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:42:50 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:42:50 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	echo_utils(char *str)
{
	int	i;

	i = -1;
	if (!str || !str[0])
		return (false);
	if (str[++i] == '-')
	{
		if (str[++i] == 'n')
			while (str[i] == 'n')
				++i;
		if (!str[i])
			return (true);
	}
	return (false);
}

void	echo_utils2(char **mtr)
{
	if (mtr[1])
	{
		ft_putmtr(++mtr);
		write(1, "\n", 1);
	}
}

int	echo_utils3(t_executor *exec)
{
	write(1, "\n", 1);
	if (exec->is_child)
	{
		free_process(exec);
		exit(0);
	}
	return (set_exit_status(exec->shell, 0), 1);
}

void	echo_utils4(bool check, char **mtr, t_executor *exec)
{
	if (!check)
		echo_utils2(mtr);
	if (exec->is_child)
	{
		free_process(exec);
		exit(0);
	}
}

bool	echo(char **mtr, t_executor *exec)
{
	int		i;
	bool	check;

	i = 0;
	check = false;
	if (!mtr[1])
		if (echo_utils3(exec))
			return (1);
	echo_utils5(mtr, check, exec, i);
	return (set_exit_status(exec->shell, 0), 1);
}
