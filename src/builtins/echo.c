/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:55:34 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/01 14:39:59 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **tokens)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (tokens[1] && ft_strncmp(tokens[1], "-n", 3) == 0)
	{
		newline = 0;
		i = 2;
	}
	while (tokens[i])
	{
		write(1, tokens[i], ft_strlen(tokens[i]));
		if (tokens[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
