/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_seperation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:53:23 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/20 17:44:48 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	is_compound_extraction(t_main *shell, t_twopointer *temp)
{
	if (shell->user_input == (temp->p_fast - 1))
		return (1);
	if (is_meta_char(*(temp->p_fast - 2)))
		return (0);
	return (1);
}

int	move_compound_token(t_twopointer *temp, int *in_quotes)
{
	while(*temp->p_fast &&\
		(get_current_quotes(in_quotes) || !is_meta_char(*temp->p_fast)))
	{
		if (*temp->p_fast == get_current_quotes(in_quotes))
		{
			change_quote_state(in_quotes, *temp->p_fast);
		}
		temp->p_fast++;
	}
	if (!*temp->p_fast && get_current_quotes(in_quotes) != 0)
	 	return (UNCLOSED_QUOTES);
	return (0);
}

int	extract_quotes(t_main *shell, t_twopointer *temp, int *in_quotes)
{
	change_quote_state(in_quotes, *temp->p_fast);
	temp->p_fast++;
	if (is_compound_extraction(shell, temp))
		return (move_compound_token(temp, in_quotes));
	while (*temp->p_fast && *temp->p_fast != get_current_quotes(in_quotes))
		temp->p_fast++;
	if (!*temp->p_fast)
		return (UNCLOSED_QUOTES);
	if (!is_meta_char(*(temp->p_fast + 1)) && *(temp->p_fast + 1))
		return (move_compound_token(temp, in_quotes));
	temp->p_slow++;
	if (add_token_at_end(shell, substr_dangeros(temp->p_slow, \
		temp->p_fast - temp->p_slow), get_token_quote_type(in_quotes), 0) \
		== MALLOC_FAIL)
		return (MALLOC_FAIL);
	change_quote_state(in_quotes, *temp->p_fast);
	temp->p_fast++;
	temp->p_slow = temp->p_fast;
	return (0);
}
