/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:45:07 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/05 13:45:07 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mini_fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

void	print_error(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		write(STDERR_FILENO, &str[i], 1);
}

bool	get_env(char **envp, t_shell *shell)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	shell->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!shell->env)
		return (false);
	i = -1;
	while (envp[++i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
		{
			while (i-- > 0)
				free(shell->env[i]);
			free(shell->env);
			shell->env = NULL;
			return (false);
		}
	}
	shell->env[i] = NULL;
	return (true);
}

char	*heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	line = NULL;
	return (line);
}
