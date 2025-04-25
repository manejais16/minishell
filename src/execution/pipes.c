/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:21:39 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/25 10:17:10 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_table	*init_command_table(t_token *token_list)
{
	t_command_table	*table;
	int				num_commands;

	if (!token_list)
		return (NULL);
	num_commands = count_commands(token_list);
	table = (t_command_table *)malloc(sizeof(t_command_table));
	if (!table)
		return (NULL);
	table->commands = NULL;
	table->num_commands = num_commands;
	table->pipe_fds = NULL;
	table->commands = parse_commands_for_pipe(token_list, num_commands);
	if (!table->commands)
	{
		free(table);
		return (NULL);
	}
	return (table);
}

int	execute_single_command_case(t_command_table *table, t_main *shell)
{
	if (table->num_commands != 1)
		return (-1);
	if (is_builtin(table->commands[0][0]))
		return (execute_builtin(table->commands[0], shell));
	else
	{
		execute_command(table->commands[0], shell);
		return (g_exit_status);
	}
}

int	execute_piped_commands_case(t_command_table *table, t_main *shell,
		pid_t *pids)
{
	int	i;
	int	result;

	if (create_pipes(table) != 0)
		return (1);
	i = 0;
	while (i < table->num_commands)
	{
		pids[i] = execute_piped_command(table->commands[i], shell, i, table);
		if (pids[i] == -1)
		{
			close_all_pipes(table);
			return (1);
		}
		i++;
	}
	close_all_pipes(table);
	result = wait_for_all_children(pids, table->num_commands);
	return (result);
}

int	execute_command_table(t_command_table *table, t_main *shell)
{
	pid_t	*pids;
	int		result;

	if (!table || table->num_commands == 0)
		return (1);
	if (table->num_commands == 1)
		return (execute_single_command_case(table, shell));
	pids = (pid_t *)malloc(sizeof(pid_t) * table->num_commands);
	if (!pids)
		return (1);
	result = execute_piped_commands_case(table, shell, pids);
	free(pids);
	pids = NULL;
	return (result);
}

int	process_pipeline(t_main *shell)
{
	t_command_table	*table;
	int				result;

	if (!shell || !shell->first_token)
		return (1);
	shell->is_child_running = 1;
	table = init_command_table(shell->first_token);
	if (!table)
		return (1);
	result = execute_command_table(table, shell);
	shell->is_child_running = 0;
	free_command_table(table);
	return (result);
}
