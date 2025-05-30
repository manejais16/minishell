/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:25:31 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 18:28:14 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static void	print_tokenisation_error(t_main *shell, char *str)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	shell->return_value = 2;
	g_exit_status = 2;
}

int	is_metachar_combination_legal(t_token *first, t_token *second)
{
	if (*first->str == '|' && (*second->str == '<' || *second->str == '>'))
		return (1);
	if (is_meta_char(*first->str) && first->quote_type == NONE
		&& is_meta_char(*second->str) && second->quote_type == NONE)
		return (0);
	return (1);
}

int	check_for_repeating_meta(t_main *shell)
{
	t_token	*temp;
	t_token	*nextp;

	if (!shell || !shell->first_token)
		return (0);
	temp = shell->first_token;
	if (*temp->str == '|' && temp->quote_type == NONE)
		return (print_tokenisation_error(shell, "|"), -1);
	while (temp)
	{
		nextp = temp->next;
		if (nextp)
		{
			if (!is_metachar_combination_legal(temp, nextp))
				return (print_tokenisation_error(shell, nextp->str), -1);
		}
		else if (is_meta_char(*temp->str) && temp->quote_type == NONE)
			return (print_tokenisation_error(shell, "newline"), -1);
		temp = nextp;
	}
	return (0);
}
