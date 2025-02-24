/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:29 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:29 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_pipe_or_redirect(char const *s, char **lst_str, t_split *split)
{
	split->s_word = split->i;
	if (ft_strncmp(&s[split->i], &s[split->i + 1], 1) == 0)
		++split->i;
	lst_str[split->j] = mini_fill_word(s, split->s_word, split->i + 1);
	if (!(lst_str[split->j]))
		return (free_split(lst_str, split->j), 0);
	split->s_word = -1;
	split->bin = true;
	split->j++;
	return (1);
}

int	split_quote(char const *s, char **lst_str, t_split *split)
{
	split->quote = ft_isquote(s[split->i]);
	if (split->bin)
	{
		split->s_word = split->i;
		split->bin = false;
	}
	++split->i;
	while (ft_isquote(s[split->i]) != split->quote && s[split->i] != 0)
		++split->i;
	if (s[split->i] == 0)
	{
		lst_str[split->j] = mini_fill_word(s, split->s_word, split->i);
		if (!(lst_str[split->j]))
			return (free_split(lst_str, split->j), 0);
		split->s_word = -1;
		split->bin = true;
		split->j++;
	}
	return (1);
}

int	split_whitespc(char const *s, char **lst_str, t_split *split)
{
	lst_str[split->j] = mini_fill_word(s, split->s_word, split->i);
	if (!(lst_str[split->j]))
		return (free_split(lst_str, split->j), 0);
	split->s_word = -1;
	split->bin = true;
	split->j++;
	if (ft_pipe_or_redirect((char *)&s[split->i]) > 0)
		--split->i;
	return (1);
}

int	cycle(char const *s, char **lst_str, t_split *split)
{
	if (ft_isquote(s[split->i]) > 0)
	{
		if (!split_quote(s, lst_str, split))
			return (0);
	}
	else if (ft_pipe_or_redirect((char *)&s[split->i]) > 0
		&& split->s_word < 0)
	{
		if (!split_pipe_or_redirect(s, lst_str, split))
			return (0);
	}
	else if (!ft_iswhitespc(s[split->i])
		&& !ft_isquote(s[split->i]) && split->s_word < 0)
	{
		split->s_word = split->i;
		split->bin = false;
	}
	else if ((ft_iswhitespc(s[split->i])
			|| ft_pipe_or_redirect((char *)&s[split->i]) > 0
			|| split->i == ft_strlen(s)) && split->s_word >= 0)
	{
		if (!split_whitespc(s, lst_str, split))
			return (0);
	}
	return (1);
}

char	**mini_makesplit(char const *s, char **lst_str)
{
	t_split	*split;

	split = init_split_var();
	while (++split->i <= ft_strlen(s))
	{
		if (!cycle(s, lst_str, split))
			return (NULL);
	}
	lst_str[split->j] = NULL;
	free(split);
	return (lst_str);
}
