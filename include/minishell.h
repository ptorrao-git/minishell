/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:33:07 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:33:07 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//=============================================================//
//=========================[TOKEN TYPES]=========================//
//=============================================================//
# define ARG 0
# define CMD 1
# define PIPE 2
# define D_PIPE 3
# define RED_OUT 4
# define RED_IN 5
# define APPEND 6
# define HERE_DOC 7
# define MINI_FILE 8
# define MINI_EOF 9

//=============================================================//
//=========================[INCLUDES]=========================//
//=============================================================//

# include "../libs//libft/get_next_line/get_next_line_bonus.h"
# include "../libs//libft/libft.h"
# include "../libs/libft/ft_printf/ft_printf.h"
# include <stdbool.h>
# include "parsing/parser.h"
# include "executor/executor.h"
# include "utils/utils.h"
# include <bits/waitflags.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

//=============================================================//
//=========================[MACROS]=========================//
//=============================================================//

//----COLORS
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define BLUE "\033[0;36m"
# define DEFAULT_COLOR "\033[0m"

//=============================================================//
//=========================[FUNCTIONS]=========================//
//=============================================================//

//=========================[MAIN]=========================//
int		minishell(t_executor *exec, char **envp);
int		executor(t_executor *exec);
int		minishell_loop(t_executor *exec, t_token **tokens);

//=========================[ENV]=========================//
void	set_exit_status(t_shell *shell, int status);
bool	get_env(char **envp, t_shell *shell);

//=========================[SYNTAX]=========================//
int		syntax_append_heredoc(t_token *token);
int		syntax_red_out(t_token *token);
int		syntax_red_in(t_token *token);
int		syntax_pipe(t_token *token);
int		syntax_checker(t_token **tokens, t_executor *exec);
int		check_quotes(t_token *token);

//=========================[SIGNAL]=========================//
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	signals(void);
void	handle_sighd(int sig);

//=========================[UTILS]=========================//
void	get_pwd(char **envp, t_shell *shell);
void	free_pwd(t_shell *shell);
void	free_strings_pwd(char *s1, char *s2);

#endif