/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:32:20 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 15:56:47 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_main *shell, int exit_code)
{
	rl_clear_history();
	if (shell->user_input)
		free(shell->user_input);
	if (shell->envp)
		shell_free_split(shell->envp);
	exit(exit_code);
}

int	ft_exit(char **tokens, t_main *shell)
{
	int	exit_code;

	if (!tokens[1])
		exit_code = 0;
	else if (!is_numeric(tokens[1]))
	{
		shell->return_value = 255;
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(tokens[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 255;
	}
	else if (tokens[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		shell->return_value = 1;
		exit_code = 1;
		return (1);
	}
	else
		exit_code = ft_atoi(tokens[1]);
	free_and_exit(shell, exit_code);
	return (0);
}
