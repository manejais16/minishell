/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:32:20 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/06 16:13:13 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TODO: Before exit codes all the allocated
memory should be freed.*/
int	ft_exit(char **tokens)
{
	int	exit_code;

	ft_printf("exit\n");

	if (!tokens[1])
		exit(0);

	if (!is_numeric(tokens[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", tokens[1]);
		exit(255);
	}

	if (tokens[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}

	exit_code = ft_atoi(tokens[1]);
	exit(exit_code);
}
