/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:37:48 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/02 10:13:27 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

// Your global exit status (ONLY global allowed)
int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**tokens;
	t_shell	shell;
	int		i;

	(void)argc;
	(void)argv;
	init_terminal_settings();
	shell.envp = copy_envp(envp);
	while (1)
	{
		setup_signals();
		input = readline("minishell> ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokens = tokenize_input(input);
		i = 0;
		while (tokens && tokens[i])
		{
			ft_printf("TOKEN[%d]: %s\n", i, tokens[i]);
			i++;
		}

		execute_command(tokens, &shell);
		ft_printf("You typed: %s\n", input);
		free_tokens(tokens);
		free(input);
	}
	return (g_exit_status);
}
