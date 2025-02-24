/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:43:45 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:43:45 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **mtr, t_executor *exec)
{
	char	cwd[MAX_PATH_LEN];

	if (mtr[1] && mtr[1][0] == '-')
	{
		w_error("pwd: can not receive arguments or options "
			"(imposed by subject)\n");
		return (set_exit_status(exec->shell, 1), 1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		ft_printf("%s\n", cwd);
	else
		w_error("ERROR READING PWD\n");
	if (exec->is_child)
	{
		free_process(exec);
		exit(0);
	}
	else
		return (set_exit_status(exec->shell, 0), 1);
	return (set_exit_status(exec->shell, 0), 1);
}
