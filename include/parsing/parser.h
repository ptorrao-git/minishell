/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:33:26 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:33:26 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//=============================================================//
//=========================[INCLUDES]=========================//
//=============================================================//

# include "minishell.h"

//=============================================================//
//=========================[STRUCTURES]=========================//
//=============================================================//

typedef struct s_split
{
	size_t	i;
	int		j;
	int		s_word;
	int		quote;
	bool	bin;
}	t_split;

typedef struct s_words
{
	int		i;
	int		quote;
	int		c_words;
	bool	bin;
}	t_words;

typedef struct s_token
{
	bool			d_quotes;
	int				type;
	char			*info;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_shell
{
	char	*line;
	int		status;
	char	**env;
	char	*pwd_str;
	char	*oldpwd_str;

}	t_shell;

typedef struct s_cmds
{
	char			*cmd;
	char			**args;
	int				fd_hd;
	struct s_cmds	*next;
	t_token			*redir;
	bool			d_quotes;
}	t_cmds;

typedef struct s_executor
{
	t_cmds	**cmds;
	t_shell	*shell;
	t_token	**token;
	int		fd_in;
	int		fd_out;
	int		*pid;
	int		n_process;
	bool	is_child;
}	t_executor;

typedef struct s_exp
{
	bool	bin;
	int		start;
	int		str_i;
	int		mtr_i;
	int		env_i;
	char	*temp;
	char	*swap;
	t_token	*token;
}	t_exp;

//=============================================================//
//=========================[FUNCTIONS]=========================//
//=============================================================//

// Lexer functions
void	lexer(t_token **tokens);
int		check_redirect_or_pipe(char *s);
int		check_file_eof(char *s);

// Expander functions
void	expander(t_token **token, t_executor *exec);
void	check_exp_temp_code(t_exp *exp, t_executor *exec);
void	check_exp_temp(t_exp *exp);
void	expand(t_exp *exp, t_executor *exec);
void	if_is_quote(t_exp *exp);
void	check_exp_temp_dollar(t_exp *exp);
void	swap_exp_code(t_exp *exp, t_executor *exec);
void	swap_exp(t_exp *exp);
int		get_env_var(t_exp *exp, t_executor *exec);

// Command functions
t_token	*get_redir(t_token *token);
t_cmds	**ft_cmd_div(t_token *token, t_executor *exec);
void	cmd_types(t_cmds **cmd, t_token **tk, t_token **tmp, t_token **begin);
bool	cmd_find_pipe(t_token **token, int *size);
bool	cmd_get_arg(t_token **temp, char **args, int *i);

// Utility functions
void	lock_count(char **s, t_words *wc);
void	unlock_count(char **s, t_words *wc);
void	remove_file(void);
char	**mini_split(char const *s);
char	**mini_makesplit(char const *s, char **lst_str);
int		mini_words(char const *s);

#endif