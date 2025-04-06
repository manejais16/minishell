/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:47 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/06 14:28:06 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TODO: Add possibility to add flags to the command*/
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

