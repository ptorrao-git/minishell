/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:23:59 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/06 16:23:59 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exp_temp_code(t_exp *exp, t_executor *exec)
{
	if (exp->temp)
		swap_exp_code(exp, exec);
	else
		exp->temp = ft_itoa(exec->shell->status);
	exp->str_i = exp->str_i + 1;
	exp->start = exp->str_i + 1;
}

void	check_exp_temp(t_exp *exp)
{
	if (exp->temp)
		swap_exp(exp);
	else
		exp->temp = ft_substr(exp->token->info, exp->start,
				(exp->str_i - exp->start));
}

void	expand(t_exp *exp, t_executor *exec)
{
	if (exp->env_i != -1)
	{
		exp->swap = ft_strjoin(exp->temp, exec->shell->env[exp->env_i]
				+ (exp->str_i - exp->start) + 1);
		free(exp->temp);
		exp->temp = NULL;
		exp->temp = ft_strdup(exp->swap);
		free(exp->swap);
		exp->swap = NULL;
	}
	exp->start = exp->str_i--;
}

void	if_is_quote(t_exp *exp)
{
	check_exp_temp(exp);
	exp->start = ++exp->str_i;
	while (ft_isquote(exp->token->info[exp->str_i]) != 1)
		exp->str_i++;
	if (exp->start != exp->str_i)
		check_exp_temp(exp);
	exp->start = exp->str_i + 1;
}
