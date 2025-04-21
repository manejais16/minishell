/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:55:26 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/21 14:05:33 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int		g_exit_status = 0;

void	print_all_tokens(t_main *shell)
{
	t_token		*temp;
	t_metachar	*meta_temp;
	t_heredoc	*here_temp;

	temp = shell->first_token;
	here_temp = shell->p_here;
	while (temp)
	{
		printf(":%s:\n", temp->str);
		meta_temp = temp->meta;
		while (meta_temp)
		{
			printf("Meta type: %-8s File name: %s\n", get_type(meta_temp->type),
				meta_temp->file_name);
			meta_temp = meta_temp->next;
		}
		temp = temp->next;
	}
	while (here_temp)
	{
		ft_printf("\nThe '%s' here:\n%s", here_temp->delimiter,
			here_temp->heredoc_input);
		here_temp = here_temp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**tokens;
	t_main	shell;
	t_token	*current;
	int		has_pipe;

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
		if (tokenize_input(&shell) == -1)
		{
			ft_printf("This is test message: Large error!!\n");
			continue ;
		}
		has_pipe = 0;
		current = shell.first_token;
		while (current)
		{
			if (is_pipe_token(current))
			{
				has_pipe = 1;
				break ;
			}
			current = current->next;
		}
		// print_all_tokens(&shell);
		if (has_pipe)
		{
			shell.return_value = process_pipeline(&shell);
			g_exit_status = shell.return_value;
		}
		else
		{
			tokens = tokens_list_to_array(shell.first_token);
			if (tokens)
			{
				if (shell.first_token)
				{
					if (execute_command_with_redirections(&shell,
							shell.first_token, tokens) < 0)
					{
						printf("Error executing command with redirections\n");
						execute_command(tokens, &shell);
					}
				}
				else
				{
					execute_command(tokens, &shell);
				}
				shell_free_split(tokens);
			}
		}
		free_user_input(&shell);
	}
	if (shell.working_dir)
		free(shell.working_dir);
	if (shell.old_working_dir)
		free(shell.old_working_dir);
	free_all_tokens(&shell);
	return (g_exit_status);
}
