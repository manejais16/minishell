/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pointer_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:23:32 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 18:26:12 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
