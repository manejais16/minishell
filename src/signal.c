/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 08:56:54 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 18:29:01 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
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
