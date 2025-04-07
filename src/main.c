/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:37:48 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/07 12:26:37 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

// Your global exit status (ONLY global allowed)
int	g_exit_status = 0;

/*TO DO: Shorten main function to 25 lines*/
int	main(int argc, char **argv, char **envp)
{
	char	**tokens;
	t_main	shell;
	int		i;

	(void)argc;
	(void)argv;
	init_terminal(&shell);
	shell.envp = copy_envp(envp);
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
		/*TODO: Store tokens in the internal structure*/
		tokens = tokenize_input(shell.user_input);
		i = 0;
		while (tokens && tokens[i])
		{
			ft_printf("TOKEN[%d]: %s\n", i, tokens[i]);
			i++;
		}
		/*TODO: Expand ENV variables*/
		//expand_variables();
		execute_command(tokens, &shell);
		ft_printf("You typed: %s\n", shell.user_input);
		/*TODO: Have to implement token freeing*/
		free_tokens(tokens);
		free(shell.user_input);
	}
	return (g_exit_status);
}
