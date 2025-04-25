/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:37:37 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/25 10:37:08 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_string(t_main *shell, char **str)
{
	int	tilde_result;

	tilde_result = 0;
	if (!str || !*str)
		return (-1);
	if ((*str)[0] == '~')
	{
		tilde_result = expand_tilde_in_string(shell, str);
		if (tilde_result == -1)
			return (-1);
	}
	find_and_expand_vars(shell, str);
	if (!*str)
		return (-1);
	return (0);
}
