/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:39:41 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/11 17:44:30 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_utils5(char **mtr, bool check, t_executor *exec, int i)
{
	if (mtr[1] && mtr[1][0] && mtr[1][0] == '-'
		&& mtr[1][1] && mtr[1][1] == 'n')
	{
		while (mtr[++i])
		{
			if (echo_utils(mtr[i]))
			{
				while (mtr[i] && echo_utils(mtr[i]))
					i++;
				if (mtr[i])
				{
					ft_putmtr(mtr + i);
					check = true;
				}
				else
				{
					check = true;
					break ;
				}
			}
			else
				break ;
		}
	}
	echo_utils4(check, mtr, exec);
}
