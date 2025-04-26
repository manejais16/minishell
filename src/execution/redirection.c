/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:24:42 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 15:21:22 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_single_redirection(t_main *shell, t_metachar *meta)
{
	int	result;

	if (meta->type == LARGER || meta->type == D_LARGER)
	{
		result = open_output_file(meta, shell);
		if (result < 0)
			return (-1);
	}
	else if (meta->type == SMALLER)
	{
		result = open_input_file(meta, shell);
		if (result < 0)
			return (-1);
	}
	else if (meta->type == 4)
	{
		result = process_heredoc(shell, meta);
		if (result < 0)
			return (-1);
	}
	return (0);
}

int	process_redirections(t_main *shell, t_token *token)
{
	t_metachar	*meta;

	if (!token || !token->meta)
		return (0);
	meta = token->meta;
	while (meta)
	{
		if (process_single_redirection(shell, meta) < 0)
			return (-1);
		meta = meta->next;
	}
	return (0);
}

int	setup_redirections(t_token *token, int *saved_stdin, int *saved_stdout)
{
	t_metachar	*meta;
	int			result;

	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		perror("minishell: dup");
		return (-1);
	}
	if (!token || !token->meta)
		return (0);
	meta = token->meta;
	while (meta)
	{
		result = setup_single_redirection(meta);
		if (result < 0)
		{
			restore_std_fds(*saved_stdin, *saved_stdout);
			return (-1);
		}
		meta = meta->next;
	}
	return (0);
}

int	prepare_redirections(t_main *shell, t_token *token, int *saved_stdin,
		int *saved_stdout)
{
	if (process_redirections(shell, token) < 0)
		return (-1);
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		perror("minishell: dup");
		close_redirections(token);
		return (-1);
	}
	if (setup_redirections(token, saved_stdin, saved_stdout) < 0)
	{
		close_redirections(token);
		return (-1);
	}
	return (0);
}

int	execute_command_with_redirections(t_main *shell, t_token *token,
		char **tokens)
{
	int	result;
	int	saved_stdin;
	int	saved_stdout;

	result = 0;
	if (prepare_redirections(shell, token, &saved_stdin, &saved_stdout) < 0)
	{
		shell->return_value = 1;
		return (-1);
	}
	execute_command(tokens, shell);
	close_redirections(token);
	restore_std_fds(saved_stdin, saved_stdout);
	return (result);
}
