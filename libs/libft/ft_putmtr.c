/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmtr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:46:17 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:46:17 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putmtr(char **mtr)
{
	int	i;

	i = -1;
	if (!mtr)
		return ;
	while (mtr[++i])
	{
		ft_printf("%s", mtr[i]);
		if (mtr[i][0] && mtr[i + 1] && mtr[i + 1][0])
			ft_printf(" ");
	}
}
