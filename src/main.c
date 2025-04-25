/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:37:48 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/25 10:25:39 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

// Your global exit status (ONLY global allowed)
int	g_exit_status = 0;

#include <stdio.h>
#include "./parsing/parsing.h"

char *get_type(t_type type)
{
	if (type == LARGER)
		return (">");
	else if (type == SMALLER)
		return ("<");
	else if (type == D_LARGER)
		return (">>");
	else if (type == D_SMALLER)
		return ("<<");
	return (NO_MATCH);
}

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
	set_shell_for_signals(&shell);
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
		/*TEST cases*/
		//print_all_tokens(&shell);
		while (current)
		{
				if (is_pipe_token(current))
				{
				has_pipe = 1;
				break ;
			}
			current = current->next;
		}
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
				//if (shell.first_token)
				//{
					//execute_command_with_redirections(&shell,
					//		shell.first_token, tokens);
					// if (execute_command_with_redirections(&shell,
					// 		shell.first_token, tokens) < 0)
					// {
						//printf("Error executing command with redirections\n");
						//execute_command(tokens, &shell);
					// }
				// }
				// else
				// {
					execute_command(tokens, &shell);
				//}
				shell_free_split(tokens);
			}
		}
		/*End of programm*/
		free_user_input(&shell);
	}
	if (shell.working_dir)
		free(shell.working_dir);
	if (shell.old_working_dir)
		free(shell.old_working_dir);
	free_all_tokens(&shell);
	return (g_exit_status);
}
