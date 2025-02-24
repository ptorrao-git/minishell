/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:43:11 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:43:11 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	w_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(STDERR_FILENO, &str[i], 1);
}

bool	check_max_min(char *str)
{
	long long	n;
	size_t		i;
	char		*str_n;

	i = 0;
	n = 0;
	i = ft_strlen(str);
	n = ft_atoll(str);
	str_n = ft_lltoa(n);
	if (str[0] == '+')
		i--;
	if (ft_strlen(str_n) != i)
	{
		free(str_n);
		return (false);
	}
	free(str_n);
	return (true);
}

void	exit_utils(t_executor *exec, int i, char **mtr)
{
	while (mtr[1][++i])
	{
		if (!ft_isdigit(mtr[1][i]) && mtr[1][0] != '-' && mtr[1][0] != '+')
		{
			set_exit_status(exec->shell, 2);
			w_error(" numeric argument required\n");
			free_process(exec);
			exit(2);
		}
	}
}

bool	exit_checker(t_executor *exec, char **mtr)
{
	if (!check_max_min(mtr[1]))
	{
		set_exit_status(exec->shell, 2);
		w_error(" numeric argument required\n");
		free_process(exec);
		exit(2);
	}
	else if (ft_strlen(mtr[1]) == 2 && mtr[1][0] == '+' && mtr[1][1] == '+')
	{
		set_exit_status(exec->shell, 2);
		w_error(" numeric argument required\n");
		free_process(exec);
		exit(2);
	}
	return (true);
}

int	exit_builtin(int status, t_executor *exec, char **mtr)
{
	int	i;

	i = -1;
	if (mtr[1])
	{
		if (ft_strlen(mtr[1]) == 2 && mtr[1][0] == '-' && mtr[1][1] == '-')
		{
			free_process(exec);
			exit (0);
		}
		exit_utils(exec, i, mtr);
		if (!exit_checker(exec, mtr))
			return (0);
		else if (mtr[1][0] == '-' || mtr[1][0] == '+')
			++i;
		else if (mtr[2])
			return (set_exit_status(exec->shell, 1),
				w_error(" too many arguments\n"), 1);
		status = ft_atoll(mtr[1]);
	}
	free_process(exec);
	exit(status % 256);
}
