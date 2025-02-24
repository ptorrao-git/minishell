/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:59 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:59 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token_utils(t_token **token, char **mtr, int i)
{
	t_token	*temp;

	temp = *token;
	while (mtr[++i])
	{
		temp->next = (t_token *)malloc(sizeof(t_token));
		if (!(temp->next))
			return ;
		temp->next->prev = temp;
		temp = temp->next;
		temp->info = ft_strdup(mtr[i]);
		temp->type = false;
		temp->type = -1;
		temp->d_quotes = false;
		temp->next = NULL;
	}
}

bool	create_token(char **mtr, t_token **token)
{
	int		i;

	i = 0;
	if (!mtr[i])
		return (false);
	*token = (t_token *)malloc(sizeof(t_token));
	if (!(*token))
		return (false);
	(*token)->info = ft_strdup(mtr[i]);
	(*token)->type = -1;
	(*token)->d_quotes = false;
	(*token)->prev = NULL;
	(*token)->next = NULL;
	create_token_utils(token, mtr, i);
	return (true);
}

t_split	*init_split_var(void)
{
	t_split	*split;

	split = malloc((1) * sizeof(t_split));
	if (!split)
	{
		w_error("Error\n");
		exit(1);
	}
	split->i = -1;
	split->j = 0;
	split->s_word = -1;
	split->quote = 0;
	split->bin = true;
	return (split);
}

t_words	*init_wc(void)
{
	t_words	*wc;

	wc = malloc((1) * sizeof(t_split));
	if (!wc)
	{
		w_error("Error\n");
		exit(1);
	}
	wc->i = 0;
	wc->quote = 0;
	wc->c_words = 0;
	wc->bin = true;
	return (wc);
}

t_executor	*init_exec(t_executor *exec)
{
	exec->shell = (t_shell *)malloc(sizeof(t_shell));
	if (!exec->shell)
		return (free(exec), NULL);
	exec->shell->status = 0;
	exec->shell->oldpwd_str = NULL;
	exec->shell->pwd_str = NULL;
	exec->token = (t_token **)malloc(sizeof(t_token));
	if (!exec->token)
	{
		free(exec->shell);
		return (free(exec), NULL);
	}
	exec->cmds = NULL;
	exec->fd_in = dup(STDIN_FILENO);
	exec->fd_out = dup(STDOUT_FILENO);
	exec->pid = NULL;
	exec->n_process = 0;
	exec->is_child = false;
	return (exec);
}
