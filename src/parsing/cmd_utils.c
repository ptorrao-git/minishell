/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:14:06 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/10 20:29:26 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_types(t_cmds **cmd, t_token **tk, t_token **tmp, t_token **begin)
{
	if (!(*tmp))
	{
		(*begin) = (t_token *)malloc(sizeof(t_token));
		(*begin)->type = (*tk)->type;
		(*begin)->info = ft_strdup((*tk)->next->info);
		*tk = (*tk)->next;
		(*begin)->next = NULL;
		(*cmd)->redir = *begin;
		*tmp = *begin;
	}
	else
	{
		(*tmp)->next = (t_token *)malloc(sizeof(t_token));
		*tmp = (*tmp)->next;
		(*tmp)->type = (*tk)->type;
		(*tmp)->info = ft_strdup((*tk)->next->info);
		*tk = (*tk)->next;
		(*tmp)->next = NULL;
	}
}

bool	cmd_find_pipe(t_token **token, int *size)
{
	if ((*token)->type == RED_IN || (*token)->type == HERE_DOC
		|| (*token)->type == APPEND || (*token)->type == RED_OUT)
		*token = (*token)->next->next;
	else if ((*token)->type == PIPE)
		return (true);
	if (*token && (*token)->type == ARG && ((*token)->info[0] != '\0'
			|| (*token)->d_quotes))
		*size += 1;
	if (*token)
		*token = (*token)->next;
	return (false);
}

bool	cmd_get_arg(t_token **temp, char **args, int *i)
{
	if ((*temp)->type == PIPE)
		return (true);
	if ((*temp)->type == RED_IN || (*temp)->type == HERE_DOC
		|| (*temp)->type == APPEND || (*temp)->type == RED_OUT)
		*temp = (*temp)->next;
	else if ((*temp)->type == ARG && ((*temp)->info[0] != '\0'
			|| (*temp)->d_quotes)
		&& (!(*temp)->prev || ((*temp)->prev->type != RED_IN
				&& (*temp)->prev->type != RED_OUT
				&& (*temp)->prev->type != APPEND
				&& (*temp)->prev->type != HERE_DOC)))
	{
		args[*i] = ft_strdup((*temp)->info);
		*i += 1;
	}
	*temp = (*temp)->next;
	return (false);
}

t_token	*get_redir(t_token *token)
{
	t_token	*redir;

	redir = (t_token *)malloc(sizeof(t_token));
	if (!redir)
		return (NULL);
	redir->type = token->type;
	redir->info = token->next->info;
	redir->next = NULL;
	return (redir);
}
