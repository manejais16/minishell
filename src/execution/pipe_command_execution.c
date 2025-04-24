/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_command_execution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:55 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/24 10:31:28 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_all_children(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) > 0)
		{
			if (i == count - 1)
			{
				if (WIFEXITED(status))
					last_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					last_status = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
	return (last_status);
}

int	is_pipe_token(t_token *token)
{
	if (!token || !token->str)
		return (0);
	if (ft_strcmp(token->str, "|") == 0 && token->quote_type == NONE)
		return (1);
	return (0);
}

void	cleanup_parsed_commands(char ***commands, int cmd_index)
{
	int	j;

	while (--cmd_index >= 0)
	{
		j = 0;
		while (commands[cmd_index][j])
			free(commands[cmd_index][j++]);
		free(commands[cmd_index]);
	}
	free(commands);
}

void	free_command_arrays(t_command_table *table)
{
	int	i;
	int	j;

	if (!table || !table->commands)
		return ;
	i = 0;
	while (i < table->num_commands)
	{
		if (table->commands[i])
		{
			j = 0;
			while (table->commands[i][j])
				free(table->commands[i][j++]);
			free(table->commands[i]);
		}
		i++;
	}
	free(table->commands);
	table->commands = NULL;
}

void	free_command_table(t_command_table *table)
{
	if (!table)
		return ;
	free_command_arrays(table);
	if (table->pipe_fds)
	{
		close_all_pipes(table);
		free(table->pipe_fds);
		table->pipe_fds = NULL;
	}
	free(table);
}
