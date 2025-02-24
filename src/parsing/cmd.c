/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:06 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:06 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_token(t_token *token)
{
	int		size;
	int		i;
	char	**args;
	t_token	*temp;

	size = 0;
	args = NULL;
	temp = token;
	i = 0;
	while (token)
		if (cmd_find_pipe(&token, &size))
			break ;
	if (size == 0)
		return (NULL);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	while (temp)
		if (cmd_get_arg(&temp, args, &i))
			break ;
	args[i] = NULL;
	return (args);
}

void	init_cmds(t_cmds **cmds)
{
	if (!cmds)
		return ;
	*cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (*cmds)
	{
		(*cmds)->cmd = NULL;
		(*cmds)->args = NULL;
		(*cmds)->redir = NULL;
		(*cmds)->next = NULL;
		(*cmds)->d_quotes = false;
		(*cmds)->fd_hd = -1;
	}
}

void	add_redirection(t_cmds *cmd, t_token *token)
{
	t_token	*redir;
	t_token	*temp;

	redir = get_redir(token);
	if (!redir)
		return ;
	if (cmd->redir)
	{
		temp = cmd->redir;
		while (temp->next)
			temp = temp->next;
		temp->next = redir;
	}
	else
	{
		cmd->redir->info = ft_strdup(redir->info);
		cmd->redir->type = redir->type;
		free(redir);
	}
}

void	ft_div(t_cmds **cmds, t_token *token)
{
	t_token	*temp;
	t_token	*begin;
	t_cmds	*cmd;

	if (!cmds || !*cmds || !token)
		return ;
	cmd = *cmds;
	begin = NULL;
	temp = NULL;
	if (token->d_quotes)
		cmd->d_quotes = true;
	cmd->args = get_token(token);
	if (cmd->args && cmd->args[0] && !cmd->cmd)
		cmd->cmd = ft_strdup(cmd->args[0]);
	while (token && token->type != PIPE)
	{
		if (token->type == RED_IN || token->type == RED_OUT
			|| token->type == APPEND || token->type == HERE_DOC)
			cmd_types(&cmd, &token, &temp, &begin);
		else
			token = token->next;
	}
	cmd->redir = (*cmds)->redir;
}

t_cmds	**ft_cmd_div(t_token *token, t_executor *exec)
{
	t_cmds	*current_cmd;

	if (!token)
		return (NULL);
	*exec->cmds = NULL;
	init_cmds(exec->cmds);
	current_cmd = *exec->cmds;
	while (token)
	{
		ft_div(&current_cmd, token);
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
		{
			init_cmds(&current_cmd->next);
			current_cmd = current_cmd->next;
			token = token->next;
		}
	}
	return (exec->cmds);
}
