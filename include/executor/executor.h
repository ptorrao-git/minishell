/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:33:36 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:33:36 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# ifndef MAX_PATH_LEN
#  define MAX_PATH_LEN 1024
# endif

//=============================================================//
//=========================[INCLUDES]=========================//
//=============================================================//

# include <stdbool.h>

//=============================================================//
//=========================[STRUCTURES]=========================//
//=============================================================//

typedef struct s_export
{
	char	**key_left;
	char	**key_right;
	char	*arg_left;
	char	*arg_right;
	bool	append;
	bool	arg_equals;
	bool	env_equals;
	bool	new_entry;
	bool	do_nothing;
}	t_export;

//=============================================================//
//=========================[FUNCTIONS]=========================//
//=============================================================//

//============================[PWD]============================//
int			pwd(char **mtr, t_executor *exec);

//============================[CD]============================//
void		cd_invalid_path(t_executor *exec);
void		cd_too_many_args(t_executor *exec);
void		cd_oldpwd(t_shell *shell);
void		cd_home(t_shell *shell);
void		cd_utils(t_shell *shell, char *current_path);
int			cd(t_shell *shell, char **mtr, t_executor *exec);

//============================[ECHO]============================//
void		echo_utils5(char **mtr, bool check, t_executor *exec, int i);
void		echo_utils4(bool check, char **mtr, t_executor *exec);
bool		echo(char **mtr, t_executor *exec);
bool		echo_utils(char *str);

//============================[ENV]============================//
bool		env(t_shell *shell, char **mtr, t_executor *exec);

//============================[EXIT]============================//
int			exit_builtin(int status, t_executor *exec, char **mtr);

//============================[UNSET]============================//
int			unset(char **mtr, t_executor *exec);

//=======================[BUILTIN UTILS]==========================//
void		update_pwd_env(t_shell *shell, char *oldpwd, char *newpwd);
char		*getenvp(char **envp, char *var);
int			is_directory(char *path);
int			check_is_dir(char *path);
int			exec_execve(char *str_path, t_executor *exec, t_cmds *cmds);

//============================[EXPORT]============================//
// PARSE
bool		parse_export_equal(char *arg, t_export *export);
bool		parse_export_no_equal(t_export *export);
bool		parse_export(char *arg, t_export *export);
// EXECUTE
void		print_export(t_export *export);
void		execute_append(t_export *export, t_executor *exec);
bool		make_new_entry(t_export *export, t_executor *exec);
bool		replace_entry(t_export *export, t_executor *exec);
bool		execute_export(t_export *export, t_executor *exec);
int			export(t_executor *exec);
// UTILS
t_export	*init_export(t_export *export, t_executor *exec);
void		free_export_args(t_export *export);
void		free_export(t_export *export);
bool		bubblesort(t_export *export);
bool		check_append(char *arg);
char		**realloc_env(char **env);
int			env_len(char **env);
int			compare_result(t_export *export, char *s1, char *s2);

//============================[EXECUTOR]============================//
void		handle_close(t_executor *exec, int *fd);
void		check_here_doc(t_token *temp, int fd_in);
void		exec_sig(int sig);
void		check_global(t_executor *exec);
bool		handle_child(t_executor *exec, t_cmds **temp, t_token *start,
				int *fd);
bool		check_builtin(t_cmds **cmds);
bool		handle_parent(t_executor *exec, t_cmds **temp, int *fd);
bool		check_red_out(t_executor *exec, t_token *temp, int fd_out);
bool		check_red_in(t_executor *exec, t_token *temp, int fd_in);
bool		check_if_append(t_executor *exec, t_token *temp, int fd_out);
bool		check_redirection(t_executor *exec, t_token *temp, int fin,
				int fout);

#endif