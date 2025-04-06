/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:18:06 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/06 15:53:54 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TODO: Have to implement flags.*/
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
