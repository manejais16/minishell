/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:55:34 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/08 08:40:46 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_flags(char **tokens, int *i)
{
	int	j;
	int	newline;

	newline = 1;
	while (tokens[*i] && tokens[*i][0] == '-')
	{
		j = 1;
		while (tokens[*i][j] == 'n')
			j++;
		if (j == 1 || tokens[*i][j] != '\0')
			break ;
		newline = 0;
		(*i)++;
	}
	return (newline);
}

int	ft_echo(char **tokens)
{
	int	i;
	int	newline;

	i = 1;
	newline = check_n_flags(tokens, &i);
	while (tokens[i])
	{
		ft_printf("%s", tokens[i]);
		if (tokens[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
