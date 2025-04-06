/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:31:04 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/06 10:42:49 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(char *path, char **tokens, char **envp)
{
	execve(path, tokens, envp);
	perror("minishell");
	free(path);
	exit(127);
}

void	execute_external(char **tokens, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = resolve_path(tokens[0], envp);
	if (!path)
	{
		ft_printf("Command not found: %s\n", tokens[0]);
		g_exit_status = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		exec_child(path, tokens, envp);
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

void execute_command(char **tokens, t_main *shell)
{
	if (!tokens || !*tokens)
		return;
	if (is_builtin(tokens[0]))
	{
		g_exit_status = execute_builtin(tokens, shell);
		return;
	}
	execute_external(tokens, shell->envp);
}
