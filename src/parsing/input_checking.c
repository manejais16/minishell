/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:25:31 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/21 18:35:22 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/*TODO: USE AFTER TESTS!!!*/
// static void	print_tokenisation_error(char *str)
// {
// 	ft_printf("minishell: syntax error near unexpected token `%s'\n", str);
// }

int	is_metachar_combination_legal(t_token *first, t_token *second)
{
	if (*first->str == '|' && (*second->str == '<' || *second->str == '>'))
		return (1);
	if (is_meta_char(*first->str) && first->quote_type == NONE\
		&& is_meta_char(*second->str) && second->quote_type == NONE)
		return (0);
	return (1);
}

int	check_for_repeating_meta(t_main *shell)
{
	t_token	*temp;
	t_token	*nextp;

	temp = shell->first_token;
	if (*temp->str == '|' && temp->quote_type == NONE)
		return (/*print_tokenisation_error("|"),*/ -1);
	while (temp)
	{
		nextp = temp->next;
		if (nextp)
		{
			if (!is_metachar_combination_legal(temp, nextp))
				return (/*print_tokenisation_error(nextp->str),*/ -1);
		}
		else if (is_meta_char(*temp->str) && temp->quote_type == NONE)
			return (/*print_tokenisation_error("newline"),*/ -1);
		temp = nextp;
	}
	return (0);
}
