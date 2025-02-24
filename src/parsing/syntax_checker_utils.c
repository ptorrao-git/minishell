/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:38 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:38 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(t_token *token)
{
	int		i;
	char	quote;

	i = -1;
	quote = '\0';
	while (token->info[++i])
	{
		if (quote == '\0')
		{
			if (token->info[i] == '\'' || token->info[i] == '\"')
				quote = token->info[i];
		}
		else if (quote == token->info[i])
			quote = '\0';
	}
	if (quote != '\0')
		return (w_error("minishell: syntax error: unclosed "
				"quotes are not available due to subject rules\n"), 0);
	return (1);
}
