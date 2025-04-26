/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:31:04 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 10:43:47 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char **tokens, t_main *shell)
{
	t_token	*token_with_meta;
	int		saved_stdin;
	int		saved_stdout;

	if (!tokens || !*tokens)
		return ;
	token_with_meta = find_token_with_meta(shell->first_token, tokens[0]);
	if (is_builtin(tokens[0]))
	{
		if (prepare_redirections(shell, token_with_meta, &saved_stdin,
				&saved_stdout) < 0)
		{
			shell->return_value = 1;
			return ;
		}
		g_exit_status = execute_builtin(tokens, shell);
		close_redirections(token_with_meta);
		restore_std_fds(saved_stdin, saved_stdout);
		return ;
	}
	execute_external(tokens, shell, token_with_meta);
}

t_token	*find_token_with_meta(t_token *first_token, char *cmd_name)
{
	t_token	*current;

	current = first_token;
	while (current)
	{
		if (current->str && ft_strcmp(current->str, cmd_name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	execute_external(char **tokens, t_main *shell, t_token *token_with_meta)
{
	pid_t	pid;
	char	*path;

	path = resolve_path(tokens[0], shell->envp);
	if (!path)
	{
		handle_command_not_found(shell, tokens, token_with_meta);
		return ;
	}
	shell->is_child_running = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		close_redirections(token_with_meta);
		shell_free_split(tokens);
		shell->is_child_running = 0;
		return ;
	}
	if (pid == 0)
		setup_and_exec_child(path, tokens, shell, token_with_meta);
	cleanup_and_wait(path, token_with_meta, pid);
	shell->is_child_running = 0;
}

void	setup_and_exec_child(char *path, char **tokens, t_main *shell,
		t_token *token_with_meta)
{
	int	saved_stdin;
	int	saved_stdout;

	if (process_redirections(shell, token_with_meta) < 0
		|| setup_redirections(token_with_meta, &saved_stdin, &saved_stdout) < 0)
	{
		free(path);
		close_redirections(token_with_meta);
		shell_free_split(tokens);
		exit(1);
	}
	execve(path, tokens, shell->envp);
	/*perror("minishell");*/
	free(path);
	close_redirections(token_with_meta);
	shell_free_split(tokens);
	exit(127);
}

void	cleanup_and_wait(char *path, t_token *token_with_meta, pid_t pid)
{
	int	status;

	free(path);
	close_redirections(token_with_meta);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
