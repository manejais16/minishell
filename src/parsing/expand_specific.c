/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specific.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:39:51 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 14:41:38 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_exit_status(t_main *main)
{
	char	*exit_status;

	exit_status = ft_itoa(main->return_value);
	return (exit_status);
}

char	*handle_just_dollar(void)
{
	char	*exit_status;

	exit_status = ft_strdup("$");
	return (exit_status);
}
