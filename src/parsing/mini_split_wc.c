/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split_wc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:24 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:24 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_values(t_words *wc)
{
	wc->i = 1;
	if (wc->bin)
		wc->c_words += 1;
	wc->bin = false;
}

void	lock_count(char **s, t_words *wc)
{
	if (ft_isquote(**s) > 0)
	{
		wc->quote = ft_isquote(**s);
		if (wc->bin)
		{
			wc->c_words += 1;
			wc->bin = false;
		}
		(*s)++;
		while (ft_isquote(**s) != wc->quote && **s != 0)
			(*s)++;
	}
	else if (ft_pipe_or_redirect(*s) > 0 && wc->i == 0)
	{
		if (ft_pipe_or_redirect(*s) == 2)
			(*s)++;
		wc->c_words += 1;
		wc->bin = true;
	}
	else if (!ft_iswhitespc(**s) && !ft_isquote(**s) && wc->i == 0)
		change_values(wc);
}

void	unlock_count(char **s, t_words *wc)
{
	if (ft_iswhitespc(**s) || ft_pipe_or_redirect(*s) > 0)
	{
		wc->i = 0;
		wc->bin = true;
	}
}

int	mini_words(char const *s)
{
	t_words	*wc;
	int		i;

	wc = init_wc();
	while (*s)
	{
		lock_count((char **)&s, wc);
		if (*s)
			s++;
		if (*s)
			unlock_count((char **)&s, wc);
	}
	i = wc->c_words;
	free(wc);
	return (i);
}
