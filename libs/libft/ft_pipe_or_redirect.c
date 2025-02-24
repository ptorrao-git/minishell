/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_or_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:22:11 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/11/07 18:55:54 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pipe_or_redirect(char *c)
{
	int	i;

	i = 0;
	if (c[i] == '|')
	{
		if (c[i + 1] == '|')
			return (2);
		return (1);
	}
	else if (c[i] == '<')
	{
		if (c[i + 1] == '<')
			return (2);
		return (1);
	}
	else if (c[i] == '>')
	{
		if (c[i + 1] == '>')
			return (2);
		return (1);
	}
	else
		return (0);
}
