/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:24:11 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/06 16:24:11 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expander_info_dollar(t_exp *exp, t_executor *exec)
{
	check_exp_temp(exp);
	exp->start = exp->str_i;
	if (exp->token->info[exp->str_i + 1] == '?')
		check_exp_temp_code(exp, exec);
	else if (ft_isdigit(exp->token->info[exp->str_i + 1]))
		exp->start = exp->str_i + 2;
	else if ((exp->token->info[exp->str_i + 1] == '"' && !exp->bin)
		|| (exp->token->info[exp->str_i + 1] == '\'' && !exp->bin))
		exp->start = exp->str_i + 1;
	else if ((exp->token->info[exp->str_i + 1] == '"' && exp->bin)
		|| !exp->token->info[exp->str_i + 1])
		check_exp_temp_dollar(exp);
	else
	{
		exp->start = ++exp->str_i;
		while (ft_isalnum(exp->token->info[exp->str_i])
			|| exp->token->info[exp->str_i] == '_')
			++exp->str_i;
		exp->env_i = get_env_var(exp, exec);
		expand(exp, exec);
	}
}

static void	expander_info_1(t_exp *exp, char value, bool bin, t_executor *exec)
{
	if (value == '9')
	{
		check_exp_temp(exp);
		if (exp->token->info[exp->str_i + 1])
			exp->start = ++exp->str_i;
		else
			exp->start = exp->str_i + 1;
	}
	else if (value == '2')
	{
		check_exp_temp(exp);
		exp->start = exp->str_i + 1;
		exp->bin = bin;
	}
	else if (value == 'w')
	{
		check_exp_temp(exp);
		exp->start = exp->str_i;
	}
	else if (value == '$')
		expander_info_dollar(exp, exec);
}

static void	expander_info_3(t_exp *exp)
{
	if (exp->token->type == ARG || exp->token->type == MINI_FILE)
	{
		free(exp->token->info);
		exp->token->info = ft_strdup(exp->temp);
		free(exp->temp);
		exp->temp = NULL;
		if (exp->swap)
		{
			free(exp->swap);
			exp->swap = NULL;
		}
		exp->env_i = -1;
		exp->str_i = -1;
		exp->start = 0;
		exp->token = exp->token->next;
	}
	else
		exp->token = exp->token->next;
}

static void	expander_ifs(t_exp *exp, t_executor *exec)
{
	if (ft_isquote(exp->token->info[exp->str_i]) == 1 && !exp->bin)
		if_is_quote(exp);
	else
	{
		if (exp->token->info[exp->str_i] == 92)
			expander_info_1(exp, '9', true, exec);
		else if (ft_isquote(exp->token->info[exp->str_i]) == 2 && !exp->bin)
			expander_info_1(exp, '2', true, exec);
		else if (ft_isquote(exp->token->info[exp->str_i]) == 2 && exp->bin)
			expander_info_1(exp, '2', false, exec);
		else if (exp->token->info[exp->str_i] == '$'
			&& ft_iswhitespc(exp->token->info[exp->str_i + 1]) > 0)
			expander_info_1(exp, 'w', false, exec);
		else if (exp->token->info[exp->str_i] == '$')
			expander_info_1(exp, '$', false, exec);
	}
}

void	expander(t_token **token, t_executor *exec)
{
	t_exp	*exp;

	exp = NULL;
	exp = init_exp(exp, token);
	while (exp->token)
	{
		if (exp->token->type == ARG || exp->token->type == MINI_FILE)
		{
			while (exp->token->info[++exp->str_i])
				expander_ifs(exp, exec);
			if (exp->start != exp->str_i)
				check_exp_temp(exp);
		}
		expander_info_3(exp);
	}
	free(exp);
}
