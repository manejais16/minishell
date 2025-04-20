/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:57:58 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/20 14:47:50 by kzarins          ###   ########.fr       */
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
/*In an ideal implementation, the heredoc could be handled as a separate 
child process,which would only receive one file descriptor. If an error
occurs, it would only close the STDOUT_FILENO side of the process. 
However, for simplicity, we can choose not to implement it this way.
It's important to keep in mind that if more than 64KB of text is entered, 
the process may become unresponsive. This is due to the blocking nature
of the write syscall, which will wait for the other side to read. In 
thisscenario, the pipe's read side could become full once the 64KB limit
is reached.*/
int	write_heredoc_to_pipe(t_heredoc *heredoc, int *pipe_fd, t_main *shell)
{
	if (heredoc->heredoc_input)
	{
		if (write(pipe_fd[1], heredoc->heredoc_input,
				ft_strlen(heredoc->heredoc_input)) == -1)
		{
			perror("minishell: write");
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
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		shell->return_value = 1;
		return (-1);
	}
	if (write_heredoc_to_pipe(heredoc, pipe_fd, shell) == -1)
		return (-1);
	meta->fd = pipe_fd[0];
	return (0);
}
