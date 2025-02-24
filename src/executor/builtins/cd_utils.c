/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:29:26 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/10 20:20:49 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_invalid_path(t_executor *exec)
{
	w_error("Invalid path\n");
	exec->shell->status = 1;
}

void	cd_too_many_args(t_executor *exec)
{
	w_error(" too many arguments\n");
	exec->shell->status = 1;
}

void	cd_home(t_shell *shell)
{
	char	*path;

	path = NULL;
	path = getenvp(shell->env, "HOME");
	if (!path)
	{
		w_error("HOME not set\n");
		shell->status = 1;
	}
	else
		chdir(getenvp(shell->env, "HOME"));
}

void	cd_oldpwd(t_shell *shell)
{
	char	*path;

	path = NULL;
	path = getenvp(shell->env, "OLDPWD");
	if (!path)
	{
		w_error("OLDPWD not set\n");
		shell->status = 1;
	}
	else
		chdir(getenvp(shell->env, "OLDPWD"));
}
