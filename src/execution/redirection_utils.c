/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 08:39:42 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/20 08:41:10 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirection_error(char *filename, char *error_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
}

int	open_output_file(t_metachar *meta, t_main *shell)
{
	int	flags;

	if (!meta || !meta->file_name)
		return (-1);
	if (meta->type == LARGER)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (meta->type == D_LARGER)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		return (-1);
	meta->fd = open(meta->file_name, flags, 0644);
	if (meta->fd == -1)
	{
		print_redirection_error(meta->file_name, strerror(errno));
		if (shell)
			shell->return_value = 1;
		return (-1);
	}
	return (0);
}

int	open_input_file(t_metachar *meta, t_main *shell)
{
	if (!meta || !meta->file_name)
		return (-1);
	meta->fd = open(meta->file_name, O_RDONLY);
	if (meta->fd == -1)
	{
		print_redirection_error(meta->file_name, "No such file or directory");
		if (shell)
			shell->return_value = 1;
		return (-1);
	}
	return (0);
}

int	setup_single_redirection(t_metachar *meta)
{
	if (!meta || meta->fd <= 0)
		return (0);
	if (meta->type == LARGER || meta->type == D_LARGER)
	{
		if (dup2(meta->fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2");
			return (-1);
		}
	}
	else if (meta->type == SMALLER || meta->type == D_SMALLER)
	{
		if (dup2(meta->fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			return (-1);
		}
	}
	return (0);
}

int	handle_empty_command_with_redirections(t_main *shell, t_token *token)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!token || !token->meta || (token->str && token->str[0] != '\0'))
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (process_redirections(shell, token) < 0 || setup_redirections(token,
			&saved_stdin, &saved_stdout) < 0)
	{
		shell->return_value = 1;
		restore_std_fds(saved_stdin, saved_stdout);
		close_redirections(token);
		return (-1);
	}
	close_redirections(token);
	restore_std_fds(saved_stdin, saved_stdout);
	return (0);
}
