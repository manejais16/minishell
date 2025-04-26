/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:28:16 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 12:36:00 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

static int	init_terminal_settings(void);
void		init_terminal_variables(t_main *shell);

void	init_terminal(t_main *shell)
{
	(void)shell;
	init_terminal_settings();
	init_terminal_variables(shell);
}

static int	init_terminal_settings(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	return (0);
}

void	init_terminal_variables(t_main *shell)
{
	shell->envp = NULL;
	shell->user_input = NULL;
	shell->working_dir = NULL;
	shell->old_working_dir = NULL;
	shell->first_token = NULL;
	shell->last_token = NULL;
	shell->p_here = NULL;
	shell->is_child_running = 0;
	shell->is_recursive = 0;
}

t_main	**get_shell_pointer_address(void)
{
	static t_main	*shell_ptr = NULL;

	return (&shell_ptr);
}

t_main	*get_shell_pointer(void)
{
	return (*get_shell_pointer_address());
}

void	set_shell_for_signals(t_main *shell)
{
	t_main	**shell_ptr_ptr;

	shell_ptr_ptr = get_shell_pointer_address();
	*shell_ptr_ptr = shell;
}

void	handle_sigint(int sig)
{
	t_main	*shell_ptr;

	(void)sig;
	write(1, "\n", 1);
	g_exit_status = 130;
	shell_ptr = get_shell_pointer();
	get_shell_pointer()->return_value = 130;
	if (shell_ptr && shell_ptr->is_child_running == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
