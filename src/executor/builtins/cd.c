/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:42:43 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:42:43 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_utils(t_shell *shell, char *current_path)
{
	char	new_path[MAX_PATH_LEN];

	getcwd(new_path, sizeof(new_path));
	update_pwd_env(shell, current_path, new_path);
}

int	cd_getcwd(t_executor *exec)
{
	w_error("Error getting current path\n");
	exec->shell->status = 1;
	if (exec->is_child)
	{
		free_process(exec);
		exit(1);
	}
	return (1);
}

void	cd_is_dir(t_shell *shell, char **mtr, char *current_path, char *str)
{
	if (mtr[1][0] == '/')
		chdir(mtr[1]);
	else
	{
		str = ft_joinpath(current_path, mtr[1]);
		chdir(str);
		free(str);
	}
	cd_utils(shell, current_path);
}

int	cd(t_shell *shell, char **mtr, t_executor *exec)
{
	char	current_path[MAX_PATH_LEN];
	char	*str;

	str = NULL;
	if (getcwd(current_path, sizeof(current_path)) == NULL)
		return (cd_getcwd(exec));
	if (!mtr[1] || (mtr[1] && !ft_strcmp(mtr[1], "~")))
		cd_home(shell);
	else if (mtr[2])
		cd_too_many_args(exec);
	else if (mtr[1] && !ft_strcmp(mtr[1], "-"))
		cd_oldpwd(shell);
	else if (mtr[1] && !is_directory(mtr[1]))
		return (set_exit_status(shell, 1),
			w_error(" No such file or directory\n"), 1);
	else if (mtr[1] && is_directory(mtr[1]))
		cd_is_dir(shell, mtr, current_path, str);
	else
		cd_invalid_path(exec);
	if (exec->is_child)
	{
		free_process(exec);
		exit(1);
	}
	return (1);
}

void	update_pwd_env(t_shell *shell, char *oldpwd, char *newpwd)
{
	char	*oldpwd_line;
	char	*newpwd_line;
	int		i;

	i = -1;
	oldpwd_line = ft_strjoin("OLDPWD=", oldpwd);
	newpwd_line = ft_strjoin("PWD=", newpwd);
	while (shell->env[++i])
	{
		if (!ft_strncmp(shell->env[i], "OLDPWD=", 7))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(oldpwd_line);
		}
	}
	i = -1;
	while (shell->env[++i])
	{
		if (!ft_strncmp(shell->env[i], "PWD=", 4))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(newpwd_line);
		}
	}
	free_strings_pwd(oldpwd_line, newpwd_line);
}
