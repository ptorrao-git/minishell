/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:53 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:53 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_split(char **str, int j)
{
	while (j--)
		free(str[j]);
	free(str);
	return (NULL);
}

void	free_mtr(char **mtr)
{
	int	j;

	j = -1;
	if (!mtr)
		return ;
	while (mtr[++j])
	{
		free(mtr[j]);
		mtr[j] = NULL;
	}
	free(mtr);
	mtr = NULL;
}

void	free_token(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		temp = token->next;
		free(token->info);
		free(token);
		token = temp;
	}
}

void	ft_free_cmds(t_cmds *cmds)
{
	t_cmds	*temp;

	while (cmds)
	{
		temp = cmds->next;
		if (cmds->cmd)
		{
			free(cmds->cmd);
			cmds->cmd = NULL;
		}
		if (cmds->args)
		{
			free_mtr(cmds->args);
			cmds->args = NULL;
		}
		if (cmds->redir)
		{
			free_token(cmds->redir);
			cmds->redir = NULL;
		}
		free(cmds);
		cmds = NULL;
		cmds = temp;
	}
}
