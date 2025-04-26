/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:37:48 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 19:10:39 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
// #include <stdio.h>
// #include "./parsing/parsing.h"

// Your global exit status (ONLY global allowed)
int	g_exit_status = 0;

void	the_shell_loop(t_main *shell);

int	main(int argc, char **argv, char **envp)
{
	t_main	shell;

	(void)argc;
	(void)argv;
	init_terminal(&shell);
	shell.envp = copy_envp(envp);
	shell.return_value = 0;
	the_shell_loop(&shell);
	if (shell.working_dir)
		free(shell.working_dir);
	if (shell.old_working_dir)
		free(shell.old_working_dir);
	free_all_tokens(&shell);
	return (g_exit_status);
}

int	has_pipe(t_main *shell)
{
	t_token	*current;

	current = shell->first_token;
	while (current)
	{
		if (is_pipe_token(current))
			return (1);
		current = current->next;
	}
	return (0);
}

int	execute_line(t_main *shell)
{
	char	**tokens;

	if (has_pipe(shell))
	{
		shell->return_value = process_pipeline(shell);
		g_exit_status = shell->return_value;
	}
	else
	{
		tokens = tokens_list_to_array(shell->first_token);
		if (tokens)
		{
			execute_command(tokens, shell);
			shell->return_value = g_exit_status;
			shell_free_split(tokens);
		}
	}
	return (0);
}

void	the_shell_loop(t_main *shell)
{
	set_shell_for_signals(shell);
	while (1)
	{
		setup_signals();
		if (shell->is_recursive)
			break ;
		shell->user_input = readline("minishell> ");
		if (!shell->user_input)
			break ;
		if (*shell->user_input == '\0')
		{
			free(shell->user_input);
			continue ;
		}
		add_history(shell->user_input);
		if (tokenize_input(shell) == -1)
			continue ;
		execute_line(shell);
		free_user_input(shell);
	}
}
