/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:55:26 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/19 12:02:20 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	g_exit_status = 0;

void	print_all_tokens(t_main *shell)
{
	t_token	*temp;
	t_metachar *meta_temp;
	t_heredoc *here_temp;
	temp = shell->first_token;
	here_temp = shell->p_here;
	while (temp)
	{
		printf(":%s:\n", temp->str);
		meta_temp = temp->meta;
		while(meta_temp)
		{
			printf("Meta type: %-8s File name: %s\n", get_type(meta_temp->type), meta_temp->file_name);
			meta_temp = meta_temp->next;
		}
		temp = temp->next;
	}
	while (here_temp)
	{
		ft_printf("\nThe '%s' here:\n%s", here_temp->delimiter, here_temp->heredoc_input);
		here_temp = here_temp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	//char	**tokens;
	t_main	shell;
	//int		parsing_result;
	//t_token	*current;

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
			printf("This is test message: Large error!!\n");
			free(shell.user_input);
			continue ;
		}
		/*This is printing all the input tokens*/
		// current = shell.first_token;
		
		print_all_tokens(&shell);
		// tokens = tokens_list_to_array(shell.first_token);
		// if (tokens)
		// {
		// 	execute_command(tokens, &shell);
		// 	shell_free_split(tokens);
		// }
		free_user_input(&shell);
	}
	if (shell.working_dir)
		free(shell.working_dir);
	if (shell.old_working_dir)
		free(shell.old_working_dir);
	free_all_tokens(&shell);
	//system("leaks test");
	return (g_exit_status);
}
