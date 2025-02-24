/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:44:33 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:44:33 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**mini_split(char const *s)
{
	char	**mtr;

	if (!s)
		return (NULL);
	mtr = malloc((mini_words(s) + 1) * sizeof(char *));
	if (!mtr)
		return (NULL);
	mtr = mini_makesplit(s, mtr);
	return (mtr);
}
