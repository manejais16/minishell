/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:55:26 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/16 18:24:36 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	g_exit_status = 0;

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;

// 	parsing_test();
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	char	**tokens;
	t_main	shell;
	int		parsing_result;
	t_token	*current;

	(void)argc;
	(void)argv;
	init_terminal(&shell);
	shell.envp = copy_envp(envp);
	shell.return_value = 42;
	while (1)
	{
		setup_signals();
		shell.user_input = readline("minishell> ");
		if (!shell.user_input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*shell.user_input == '\0')
		{
			free(shell.user_input);
			continue ;
		}
		add_history(shell.user_input);
		parsing_result = go_through_str(&shell);
		if (parsing_result < 0)
		{
			ft_printf("Parsing error: %d\n", parsing_result);
			free(shell.user_input);
			continue ;
		}
		current = shell.first_token;
		while (current)
		{
			expand_tilde(&shell, current);
			current = current->next;
		}
		expand_variables(&shell);
		tokens = tokens_list_to_array(shell.first_token);
		if (tokens)
		{
			execute_command(tokens, &shell);
			shell_free_split(tokens);
		}
		free_all_tokens(&shell);
		free(shell.user_input);
	}
	if (shell.working_dir)
		free(shell.working_dir);
	if (shell.old_working_dir)
		free(shell.old_working_dir);
	shell_free_split(shell.envp);
	return (g_exit_status);
}
