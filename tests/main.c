/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:55:26 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/08 15:41:40 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	parsing_test();
	return (0);
}
