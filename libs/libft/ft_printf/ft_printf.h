/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:39:58 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/05/24 18:37:44 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_printf(const char *string, ...);

int		ft_putstr(char *s);
int		ft_putchar(char c);
int		ft_putnbr(int nb);
int		ft_hexa(unsigned int nb, const char c);
int		ft_uputnbr(unsigned int nb);
int		ft_pointer(unsigned long nb);

#endif