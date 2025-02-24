/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-fe <ddias-fe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:43 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/06 15:02:05 by ddias-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_checker(t_token **tokens, t_executor *exec)
{
	t_token	*token;

	token = *tokens;
	if (!token || token->info[0] == '\0')
		return (ft_printf("\n"), 0);
	while (token)
	{
		if (!check_quotes(token))
			return (exec->shell->status = 2, 0);
		if (!syntax_pipe(token) || !syntax_red_out(token)
			|| !syntax_append_heredoc(token) || !syntax_red_in(token))
			return (exec->shell->status = 2, 0);
		token = token->next;
	}
	return (1);
}

int	syntax_pipe(t_token *token)
{
	if (token->type == PIPE && !token->next)
		return (w_error(" syntax error near unexpected token `|'\n"), 0);
	if (token->type == PIPE && !token->prev)
		return (w_error(" syntax error near unexpected token `|'\n"), 0);
	if (token->type == PIPE && token->next->type == PIPE)
		return (w_error(" syntax error near unexpected token `|'\n"), 0);
	if (token->type == D_PIPE)
		return (w_error(" syntax error near unexpected token `||'\n"), 0);
	return (1);
}

int	syntax_red_out(t_token *token)
{
	if (token->type == RED_OUT && !token->next)
		return (w_error(" syntax error near unexpected token `newline'\n"), 0);
	if (token->type == RED_OUT && token->next->type == RED_OUT)
		return (w_error(" syntax error near unexpected token `>'\n"), 0);
	if (token->type == RED_OUT && token->next->type == RED_IN)
		return (w_error(" syntax error near unexpected token `<'\n"), 0);
	if (token->type == RED_OUT && token->next->type == APPEND)
		return (w_error(" syntax error near unexpected token `>>'\n"), 0);
	if (token->type == RED_OUT && token->next->type == HERE_DOC)
		return (w_error(" syntax error near unexpected token `<<'\n"), 0);
	if (token->type == RED_OUT && token->next->type == PIPE)
		return (w_error(" syntax error near unexpected token `|'\n"), 0);
	return (1);
}

int	syntax_red_in(t_token *token)
{
	if (token->type == RED_IN && !token->next)
		return (w_error(" syntax error near unexpected token `newline'\n"), 0);
	if (token->type == RED_IN && token->next->type == RED_OUT)
		return (w_error(" syntax error near unexpected token `>'\n"), 0);
	if (token->type == RED_IN && token->next->type == RED_IN)
		return (w_error(" syntax error near unexpected token `<'\n"), 0);
	if (token->type == RED_IN && token->next->type == APPEND)
		return (w_error(" syntax error near unexpected token `>>'\n"), 0);
	if (token->type == RED_IN && token->next->type == HERE_DOC)
		return (w_error(" syntax error near unexpected token `<<'\n"), 0);
	if (token->type == RED_IN && token->next->type == PIPE)
		return (w_error(" syntax error near unexpected token `|'\n"), 0);
	return (1);
}

int	syntax_append_heredoc(t_token *token)
{
	if (token->type == APPEND && !token->next)
		return (w_error(" syntax error near unexpected token `newline'\n"), 0);
	if (token->type == APPEND && (token->next->type == APPEND
			|| token->next->type == RED_OUT || token->next->type == HERE_DOC
			|| token->next->type == PIPE || token->next->type == RED_IN))
		return (w_error(" syntax error near unexpected token `>>'\n"), 0);
	if (token->type == HERE_DOC && !token->next)
		return (w_error(" syntax error near unexpected token `newline'\n"), 0);
	if (token->type == HERE_DOC && (token->next->type == HERE_DOC
			|| token->next->type == RED_OUT || token->next->type == APPEND
			|| token->next->type == PIPE || token->next->type == RED_IN))
		return (w_error(" syntax error near unexpected token `<<'\n"), 0);
	return (1);
}
