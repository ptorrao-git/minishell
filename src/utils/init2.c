/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:45:03 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:45:03 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*init_exp(t_exp	*exp, t_token **token)
{
	exp = (t_exp *)malloc(sizeof(t_exp));
	exp->bin = false;
	exp->start = 0;
	exp->str_i = -1;
	exp->mtr_i = -1;
	exp->env_i = -1;
	exp->temp = NULL;
	exp->swap = NULL;
	exp->token = *token;
	return (exp);
}
