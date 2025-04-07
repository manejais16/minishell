/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:32:20 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/07 10:39:27 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **tokens, t_main *shell)
{
	int	exit_code;

	ft_printf("exit\n");
	if (!tokens[1])
		exit_code = 0;
	else if (!is_numeric(tokens[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n",
			tokens[1]);
		exit_code = 255;
	}
	else if (tokens[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else
		exit_code = ft_atoi(tokens[1]);
	rl_clear_history();
	if (shell->user_input)
		free(shell->user_input);
	if (shell->envp)
		shell_free_split(shell->envp);
	exit(exit_code);
}
