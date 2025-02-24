/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:17:25 by ddias-fe          #+#    #+#             */
/*   Updated: 2025/02/06 11:17:25 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_export_equal(char *arg, t_export *export)
{
	size_t	i;

	i = -1;
	export->arg_right = ft_strdup(ft_strchr(arg, '=') + 1);
	export->arg_equals = true;
	export->do_nothing = false;
	if (export->arg_left[ft_strlen(export->arg_left) - 1] == '+')
		export->append = true;
	while (export->arg_left[++i])
	{
		if (export->append && i == ft_strlen(export->arg_left) - 1
			&& export->arg_left[i] == '+')
			break ;
		if ((!ft_isalpha(export->arg_left[0]) && export->arg_left[i] != '_')
			|| ft_strlen(export->arg_left) == 0
			|| (!ft_isalnum(export->arg_left[i])
				&& export->arg_left[i] != '_'))
			return (print_error("minishell: export: not a valid identifier\n"),
				false);
	}
	i = -1;
	return (true);
}

bool	parse_export_no_equal(t_export *export)
{
	size_t	i;

	i = -1;
	export->arg_right = NULL;
	export->arg_equals = false;
	while (export->arg_left[++i])
	{
		if ((!ft_isalpha(export->arg_left[0]) && export->arg_left[i] != '_')
			|| ft_strlen(export->arg_left) == 0
			|| (!ft_isalnum(export->arg_left[i])
				&& export->arg_left[i] != '_'))
			return (print_error("minishell: export: not a valid identifier\n"),
				false);
	}
	if (!export->new_entry)
		export->do_nothing = true;
	else
		export->do_nothing = false;
	return (true);
}

static void	parse_export_kl(t_export *export)
{
	int	i;

	i = -1;
	while (export->key_left[++i])
	{
		if (ft_strcmp(export->key_left[i], export->arg_left) == 0
			&& !ft_strchr(export->arg_left, '+'))
		{
			export->new_entry = false;
			break ;
		}
		else if (ft_strncmp(export->key_left[i], export->arg_left,
				ft_strlen(export->arg_left) - 1) == 0
			&& ft_strchr(export->arg_left, '+'))
		{
			export->new_entry = false;
			export->append = true;
			break ;
		}
	}
}

bool	parse_export(char *arg, t_export *export)
{
	if (arg[0] == '=' || arg[0] == '+')
		return (print_error("minishell: export: not a valid identifier\n"),
			false);
	if (arg[0] == '-')
		return (print_error("minishell: export: options are not suposed\n"),
			false);
	export->arg_left = ft_strndup(arg, ft_strclen(arg, '='));
	export->new_entry = true;
	parse_export_kl(export);
	if (ft_strchr(arg, '='))
		return (parse_export_equal(arg, export));
	else
		return (parse_export_no_equal(export));
	return (true);
}
