/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:43:12 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/11 17:43:12 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(t_executor *exec, char **envp)
{
	if (!get_env(envp, exec->shell))
		return (0);
	exec->cmds = (t_cmds **)malloc(sizeof(t_cmds));
	if (!exec->cmds)
		return (0);
	while (minishell_loop(exec, exec->token))
		;
	return (0);
}

void	end_main(t_executor *exec)
{
	dup2(exec->fd_out, STDOUT_FILENO);
	dup2(exec->fd_in, STDIN_FILENO);
	wait_pid(exec);
	free_all(exec);
	remove_file();
}

bool	tokens_and_lexer(t_token **tokens, char **mtr)
{
	if (!create_token(mtr, tokens))
		return (free_mtr(mtr), false);
	free_mtr(mtr);
	lexer(tokens);
	return (true);
}

int	minishell_loop(t_executor *exec, t_token **tokens)
{
	char	**mtr;

	signals();
	exec->shell->line = readline("minishell$ ");
	check_global(exec);
	if (!exec->shell->line)
		return (free_d(exec), free(exec), write(1, "exit\n", 5), exit(0), 0);
	if (exec->shell->line)
		add_history(exec->shell->line);
	if (!exec->shell->line[0])
		return (free(exec->shell->line), 1);
	mtr = mini_split(exec->shell->line);
	if (!tokens_and_lexer(tokens, mtr))
		return (1);
	if (!syntax_checker(tokens, exec))
		return (free_token(*tokens), 1);
	expander(tokens, exec);
	ft_cmd_div(*tokens, exec);
	free_token(*tokens);
	if (find_heredoc(exec->cmds, exec))
		executor(exec);
	end_main(exec);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_executor	*exec;

	(void)argc;
	(void)argv;
	exec = (t_executor *)malloc(sizeof(t_executor));
	if (!exec)
		return (-1);
	exec = init_exec(exec);
	if (!exec)
		return (-1);
	minishell(exec, envp);
	return (0);
}
