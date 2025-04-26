/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:57:58 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 15:31:31 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_redirections(t_token *token)
{
	t_metachar	*meta;

	if (!token || !token->meta)
		return ;
	meta = token->meta;
	while (meta)
	{
		if (meta->fd > 0)
		{
			close(meta->fd);
			meta->fd = -1;
		}
		meta = meta->next;
	}
}

t_heredoc	*find_heredoc(t_main *shell, char *delimiter)
{
	t_heredoc	*heredoc;

	if (!shell || !delimiter)
		return (NULL);
	heredoc = shell->p_here;
	while (heredoc)
	{
		if (ft_strcmp(heredoc->delimiter, delimiter) == 0
			&& !heredoc->already_used)
			return (heredoc);
		heredoc = heredoc->next;
	}
	return (NULL);
}

int	write_heredoc_to_pipe(t_heredoc *heredoc, int *pipe_fd, t_main *shell)
{
	if (heredoc->heredoc_input)
	{
		if (write(pipe_fd[1], heredoc->heredoc_input,
				ft_strlen(heredoc->heredoc_input)) == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			shell->return_value = 1;
			return (-1);
		}
	}
	close(pipe_fd[1]);
	heredoc->already_used = true;
	return (0);
}

static int	setup_heredoc_pipe(t_main *shell, t_heredoc *heredoc, int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		shell->return_value = 1;
		return (-1);
	}
	if (heredoc->heredoc_input)
	{
		if (write(pipe_fd[1], heredoc->heredoc_input,
				ft_strlen(heredoc->heredoc_input)) == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return (-1);
		}
	}
	close(pipe_fd[1]);
	return (0);
}

int	process_heredoc(t_main *shell, t_metachar *meta)
{
	t_heredoc	*heredoc;
	int			pipe_fd[2];

	if (!shell || !meta || !meta->file_name)
		return (-1);
	heredoc = find_heredoc(shell, meta->file_name);
	if (!heredoc)
	{
		print_redirection_error(meta->file_name, "heredoc not found");
		shell->return_value = 1;
		return (-1);
	}
	if (setup_heredoc_pipe(shell, heredoc, pipe_fd) == -1)
	{
		shell->return_value = 1;
		return (-1);
	}
	meta->fd = pipe_fd[0];
	return (0);
}
