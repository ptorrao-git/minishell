/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:24:04 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/06 16:24:04 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_var(t_exp *exp, t_executor *exec)
{
	int	i;

	i = -1;
	while (exec->shell->env[++exp->mtr_i])
	{
		if (ft_strncmp(exp->token->info + exp->start,
				exec->shell->env[exp->mtr_i], exp->str_i - exp->start) == 0
			&& exec->shell->env[exp->mtr_i][exp->str_i - exp->start] == '=')
			i = exp->mtr_i;
	}
	exp->mtr_i = -1;
	return (i);
}

void	swap_exp(t_exp *exp)
{
	char	*temp;

	temp = NULL;
	temp = ft_substr(exp->token->info, exp->start, exp->str_i - exp->start);
	exp->swap = ft_strjoin(exp->temp, temp);
	free(temp);
	if (exp->temp)
	{
		free(exp->temp);
		exp->temp = NULL;
	}
	exp->temp = ft_strdup(exp->swap);
	free(exp->swap);
	exp->swap = NULL;
}

void	swap_exp_dollar(t_exp *exp)
{
	char	*temp;

	temp = NULL;
	temp = ft_substr(exp->token->info, exp->start,
			(exp->str_i + 1) - exp->start);
	exp->swap = ft_strjoin(exp->temp, temp);
	free(temp);
	if (exp->temp)
	{
		free(exp->temp);
		exp->temp = NULL;
	}
	exp->temp = ft_strdup(exp->swap);
	free(exp->swap);
	exp->swap = NULL;
}

void	check_exp_temp_dollar(t_exp *exp)
{
	if (exp->temp)
		swap_exp_dollar(exp);
	else
		exp->temp = ft_substr(exp->token->info, exp->start,
				(exp->str_i - exp->start));
	exp->start++;
}

void	swap_exp_code(t_exp *exp, t_executor *exec)
{
	char	*temp;

	temp = NULL;
	temp = ft_itoa(exec->shell->status);
	exp->swap = ft_strjoin(exp->temp, temp);
	free(temp);
	if (exp->temp)
	{
		free(exp->temp);
		exp->temp = NULL;
	}
	exp->temp = ft_strdup(exp->swap);
	free(exp->swap);
	exp->swap = NULL;
}
