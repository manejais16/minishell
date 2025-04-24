/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:08:57 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/24 10:35:37 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes(t_command_table *table)
{
	int	i;

	if (!table || table->num_commands <= 1)
		return (0);
	if (allocate_pipe_memory(table) != 0)
		return (1);
	i = 0;
	while (i < table->num_commands - 1)
	{
		if (pipe(table->pipe_fds[i]) == -1)
		{
			while (--i >= 0)
			{
				close(table->pipe_fds[i][0]);
				close(table->pipe_fds[i][1]);
			}
			free(table->pipe_fds);
			table->pipe_fds = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

int	allocate_pipe_memory(t_command_table *table)
{
	if (!table || table->num_commands <= 1 || table->pipe_fds)
		return (0);
	table->pipe_fds = (int (*)[2])malloc(sizeof(int [2]) * (table->num_commands
				- 1));
	if (!table->pipe_fds)
		return (1);
	return (0);
}

void	close_all_pipes(t_command_table *table)
{
	int	i;

	if (!table || !table->pipe_fds)
		return ;
	i = 0;
	while (i < table->num_commands - 1)
	{
		close(table->pipe_fds[i][0]);
		close(table->pipe_fds[i][1]);
		i++;
	}
}

int	setup_child_pipes(t_command_table *table, int cmd_index)
{
	if (cmd_index > 0)
	{
		if (dup2(table->pipe_fds[cmd_index - 1][0], STDIN_FILENO) == -1)
		{
			/*perror("dup2");*/
			return (1);
		}
	}
	if (cmd_index < table->num_commands - 1)
	{
		if (dup2(table->pipe_fds[cmd_index][1], STDOUT_FILENO) == -1)
		{
			/*perror("dup2");*/
			return (1);
		}
	}
	return (0);
}

int	execute_piped_command(char **cmd_args, t_main *shell, int cmd_index,
		t_command_table *table)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		/*perror("fork");*/
		return (-1);
	}
	if (pid == 0)
	{
		if (setup_child_pipes(table, cmd_index) != 0)
			exit(1);
		close_all_pipes(table);
		if (is_builtin(cmd_args[0]))
			exit(execute_builtin(cmd_args, shell));
		else
			execute_command(cmd_args, shell);
		exit(0);
	}
	return (pid);
}
