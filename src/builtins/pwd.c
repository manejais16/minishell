/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:18:06 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/01 15:24:13 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_pwd(char **tokens)
{
	char	*cwd;
	(void)tokens;
	cwd = getcwd(NULL, 0);
	if(!cwd)
	{
		perror("pwd");
		return(1);
	}
	ft_printf("%s\n", cwd);

	free(cwd);
	return (0);
}
