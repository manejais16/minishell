/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:37:48 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/23 15:46:40 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

// Your global exit status (ONLY global allowed)
int	g_exit_status = 0;

// /*TO DO: Shorten main function to 25 lines*/
// int	main(int argc, char **argv, char **envp)
// {
// 	char	**tokens;
// 	t_main	shell;
// 	int		i;

// 	(void)argc;
// 	(void)argv;
// 	init_terminal(&shell);
// 	shell.envp = copy_envp(envp);
// 	while (1)
// 	{
// 		setup_signals();
// 		shell.user_input = readline("minishell> ");
// 		if (!shell.user_input)
// 		{
// 			ft_printf("exit\n");
// 			break ;
// 		}
// 		if (*shell.user_input == '\0')
// 		{
// 			free(shell.user_input);
// 			continue ;
// 		}
// 		add_history(shell.user_input);
// 		/*TODO: Store tokens in the internal structure*/
// 		tokens = tokenize_input(shell.user_input);
// 		i = 0;
// 		while (tokens && tokens[i])
// 		{
// 			ft_printf("TOKEN[%d]: %s\n", i, tokens[i]);
// 			i++;
// 		}
// 		/*TODO: Expand ENV variables*/
// 		//expand_variables();
// 		execute_command(tokens, &shell);
// 		ft_printf("You typed: %s\n", shell.user_input);
// 		/*TODO: Have to implement token freeing*/
// 		free_tokens(tokens);
// 		free(shell.user_input);
// 	}
// 	return (g_exit_status);
// }

/*TODO: remove the test functionality and add the error messages!*/
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
	shell.return_value = 0;
	while (1)
	{
		setup_signals();
		//shell.user_input = readline("minishell> ");

		if (isatty(fileno(stdin)))
			shell.user_input = readline("minishell> ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			shell.user_input = ft_strtrim(line, "\n");
			free(line);
		}
		if (!shell.user_input)
		{
			//ft_printf("exit\n");
			break ;
		}
		if (*shell.user_input == '\0')
		{
			free(shell.user_input);
			continue ;
		}
		add_history(shell.user_input);
		if (tokenize_input(&shell) == -1)
			continue ;
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
