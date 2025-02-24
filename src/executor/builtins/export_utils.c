/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:42:31 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/02/06 14:42:31 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	bubblesort(t_export *export)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (export->key_left[++i])
	{
		j = i;
		while (export->key_left[++j])
		{
			if (ft_strncmp(export->key_left[i], export->key_left[j],
					ft_strlen(export->key_left[i]) + 1) > 0)
			{
				temp = export->key_left[i];
				export->key_left[i] = export->key_left[j];
				export->key_left[j] = temp;
				temp = export->key_right[i];
				export->key_right[i] = export->key_right[j];
				export->key_right[j] = temp;
			}
		}
	}
	return (1);
}

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

t_export	*init_export(t_export *export, t_executor *exec)
{
	int	i;
	int	env_size;

	i = -1;
	env_size = env_len(exec->shell->env);
	export->append = false;
	export->arg_left = NULL;
	export->arg_right = NULL;
	export->key_left = malloc(sizeof(char *) * (env_size + 1));
	export->key_right = malloc(sizeof(char *) * (env_size + 1));
	if (!export->key_left || !export->key_right)
		return (NULL);
	while (exec->shell->env[++i])
	{
		export->key_left[i] = ft_strndup(exec->shell->env[i],
				ft_strclen(exec->shell->env[i], '='));
		if (ft_strchr(exec->shell->env[i], '='))
			export->key_right[i] = ft_strdup(ft_strchr(exec->shell->env[i], '=')
					+ 1);
		else
			export->key_right[i] = NULL;
	}
	export->key_left[i] = NULL;
	export->key_right[i] = NULL;
	return (export);
}

void	free_export(t_export *export)
{
	int	i;

	i = -1;
	while (export->key_left[++i])
	{
		free(export->key_left[i]);
		if (export->key_right[i])
			free(export->key_right[i]);
	}
	if (export->key_left)
		free(export->key_left);
	if (export->key_right)
		free(export->key_right);
	free(export);
}

void	free_export_args(t_export *export)
{
	if (export->arg_left)
		free(export->arg_left);
	if (export->arg_right)
		free(export->arg_right);
}
