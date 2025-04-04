/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:32:20 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/01 15:57:06 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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

