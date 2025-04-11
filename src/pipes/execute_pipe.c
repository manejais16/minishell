/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:43:47 by blohrer           #+#    #+#             */
/*   Updated: 2025/02/08 09:38:47 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
	{
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}
}

void	execute_child(char **cmd_args, int fd_in, int fd_out, int close_fd)
{
	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error with dup2");
		exit(EXIT_FAILURE);
	}
	close(close_fd);
	execve(cmd_args[0], cmd_args, NULL);
	perror("Error executing command");
	exit(EXIT_FAILURE);
}

void	execute_pipe(char **cmd1_args, char **cmd2_args, int fd_in, int fd_out)
{
	int		pipe_fds[2];
	pid_t	pid1;
	pid_t	pid2;

	create_pipe(pipe_fds);
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Error with fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		execute_child(cmd1_args, fd_in, pipe_fds[1], pipe_fds[0]);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Error with fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
		execute_child(cmd2_args, pipe_fds[0], fd_out, pipe_fds[1]);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
