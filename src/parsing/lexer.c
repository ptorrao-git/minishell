/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:20 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:20 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect_or_pipe(char *s)
{
	if (ft_strcmp(s, "<") == 0)
		return (RED_IN);
	else if (ft_strcmp(s, ">") == 0)
		return (RED_OUT);
	else if (ft_strcmp(s, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(s, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(s, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(s, "||") == 0)
		return (D_PIPE);
	else
		return (-1);
}

int	check_file_eof(char *s)
{
	if (ft_strcmp(s, ">") == 0
		|| ft_strcmp(s, ">>") == 0
		|| ft_strcmp(s, "<") == 0)
		return (MINI_FILE);
	else if (ft_strcmp(s, "<<") == 0)
		return (MINI_EOF);
	else
		return (-1);
}

void	lexer(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	if (check_redirect_or_pipe(temp->info) > 0)
		temp->type = check_redirect_or_pipe(temp->info);
	else
		temp->type = ARG;
	if (!ft_strcmp(temp->info, "\"\"") && ft_strlen(temp->info) == 2)
		temp->d_quotes = true;
	temp = temp->next;
	while (temp)
	{
		if (check_file_eof(temp->prev->info) > 0
			&& check_redirect_or_pipe(temp->info) < 0)
			temp->type = check_file_eof(temp->prev->info);
		else if (check_redirect_or_pipe(temp->info) > 0)
			temp->type = check_redirect_or_pipe(temp->info);
		else
			temp->type = ARG;
		if (!ft_strcmp(temp->info, "\"\"") && ft_strlen(temp->info) == 2)
			temp->d_quotes = true;
		temp = temp->next;
	}
}
