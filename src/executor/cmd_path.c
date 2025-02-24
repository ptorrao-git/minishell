/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:42:20 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/06 15:01:17 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_path(t_executor *exec, char *cmd)
{
	char	*path;
	char	**s_path;
	int		i;

	i = -1;
	path = NULL;
	s_path = NULL;
	path = getenvp(exec->shell->env, "PATH");
	s_path = ft_split(path, ':');
	while (s_path && s_path[++i])
	{
		path = NULL;
		path = ft_strjoin(s_path[i], "/");
		path = free_join(path, cmd);
		if (!access(path, F_OK))
			return (free_mtr(s_path), path);
		free(path);
	}
	if (s_path)
		free_mtr(s_path);
	print_error(cmd);
	print_error(": command not found\n");
	free_process(exec);
	exit(127);
}
