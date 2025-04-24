/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:11:46 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/24 10:13:17 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
