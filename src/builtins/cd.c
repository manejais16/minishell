/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:47 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/01 16:34:15 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_cd(char **tokens)
{
	char *target;

	if (tokens[1] == NULL)
		target = getenv("HOME");
	else
		target = tokens[1];

	if (tokens[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}

	if (!target)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}

	if (chdir(target) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

