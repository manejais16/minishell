/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:55:26 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/08 14:42:59 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This should include all the function tests*/
#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	ft_printf("hello\n");
	return(0);
}