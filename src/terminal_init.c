/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:28:16 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/19 21:34:05 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static int		init_terminal_settings(void);
void			init_terminal_variables(t_main *shell);

void	init_terminal(t_main *shell)
{
	(void)shell;
	init_terminal_settings();
	init_terminal_variables(shell);
}

static int		init_terminal_settings(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	return (0);
}

void		init_terminal_variables(t_main *shell)
{
	shell->envp = NULL;
	shell->user_input = NULL;
	shell->working_dir = NULL;
	shell->old_working_dir = NULL;
	shell->first_token = NULL;
	shell->last_token = NULL;
	shell->p_here = NULL;
}