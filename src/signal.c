/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 08:56:54 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 12:24:36 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	//signal(SIGINT, handle_sigint);
	struct sigaction	ac;

	ft_memset(&ac, 0, sizeof(struct sigaction));
	ac.sa_handler = &handle_sigint;
	sigaction(SIGINT, &ac, NULL);
	signal(SIGQUIT, handle_sigquit);
}


void	handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}
// void	setup_signals(void)
// {
// 	struct sigaction sa_int;
// 	struct sigaction sa_quit;

// 	// Ctrl-C handler
// 	sa_int.sa_handler = handle_sigint;
// 	sigemptyset(&sa_int.sa_mask);
// 	sa_int.sa_flags = SA_RESTART;  // <- this makes readline recover
// 	sigaction(SIGINT, &sa_int, NULL);

// 	// Ctrl-\ handler
// 	sa_quit.sa_handler = handle_sigquit;
// 	sigemptyset(&sa_quit.sa_mask);
// 	sa_quit.sa_flags = 0;
// 	sigaction(SIGQUIT, &sa_quit, NULL);
// }
