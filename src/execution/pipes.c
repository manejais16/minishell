/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:21:39 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/23 15:59:38 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_token(t_token *token)
{
	if (!token || !token->str)
		return (0);
	if (ft_strcmp(token->str, "|") == 0)
		return (1);
	return (0);
}

int	count_commands(t_token *token_list)
{
	int		count;
	t_token	*current;

	count = 1;
	current = token_list;
	while (current)
	{
		if (is_pipe_token(current))
			count++;
		current = current->next;
	}
	return (count);
}

int	allocate_pipe_memory(t_command_table *table)
{
	if (!table || table->num_commands <= 1 || table->pipe_fds)
		return (0);
	table->pipe_fds = (int(*)[2])malloc(sizeof(int[2]) * (table->num_commands
				- 1));
	if (!table->pipe_fds)
		return (1);
	return (0);
}

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

int	count_args_until_pipe(t_token *start)
{
	int		count;
	t_token	*current;

	count = 0;
	current = start;
	while (current && !is_pipe_token(current))
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**create_args_array(t_token *start, int arg_count)
{
	char	**args;
	t_token	*current;
	int		i;

	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	current = start;
	i = 0;
	while (i < arg_count)
	{
		args[i] = ft_strdup(current->str);
		if (!args[i])
		{
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	args[i] = NULL;
	return (args);
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

int	process_single_command(char ***commands, int cmd_index, t_token **current,
		int *remaining_commands)
{
	int	arg_count;

	arg_count = count_args_until_pipe(*current);
	commands[cmd_index] = create_args_array(*current, arg_count);
	if (!commands[cmd_index])
		return (1);
	while (arg_count > 0)
	{
		*current = (*current)->next;
		arg_count--;
	}
	if (*current && is_pipe_token(*current))
		*current = (*current)->next;
	(*remaining_commands)--;
	return (0);
}

char	***parse_commands_for_pipe(t_token *token_list, int num_commands)
{
	char	***commands;
	int		cmd_index;
	t_token	*current;
	int		remaining_commands;

	commands = (char ***)malloc(sizeof(char **) * (num_commands + 1));
	if (!commands)
		return (NULL);
	cmd_index = 0;
	current = token_list;
	remaining_commands = num_commands;
	while (current && remaining_commands > 0)
	{
		if (process_single_command(commands, cmd_index, &current,
				&remaining_commands))
		{
			cleanup_parsed_commands(commands, cmd_index);
			return (NULL);
		}
		cmd_index++;
	}
	commands[cmd_index] = NULL;
	return (commands);
}

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
	table = init_command_table(shell->first_token);
	if (!table)
		return (1);
	result = execute_command_table(table, shell);
	free_command_table(table);
	return (result);
}
