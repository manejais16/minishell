/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_extraction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:27:32 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 16:29:56 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	extract_segment(t_main *shell, t_twopointer *temp)
{
	while (*temp->p_fast && !is_quotes(*temp->p_fast) && (*temp->p_fast != '$'
			|| *temp->p_fast == *temp->p_slow))
		temp->p_fast++;
	if (add_token_at_end(shell, substr_dangeros(temp->p_slow, temp->p_fast
				- temp->p_slow), NONE, 0) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	temp->p_slow = temp->p_fast;
	return (0);
}

int	extract_unquoted_segment(t_main *shell, t_twopointer *temp, int *return_val)
{
	*return_val = extract_segment(shell, temp);
	if (*return_val < 0)
		return (*return_val);
	return (0);
}

int	extract_quote_segment(t_main *shell, t_twopointer *temp, int *in_quotes)
{
	change_quote_state(in_quotes, *temp->p_fast);
	temp->p_slow++;
	temp->p_fast++;
	while (*temp->p_fast && *temp->p_fast != get_current_quotes(in_quotes))
		temp->p_fast++;
	if (*temp->p_fast)
	{
		if (add_token_at_end(shell, substr_dangeros(temp->p_slow, temp->p_fast
					- temp->p_slow), get_token_quote_type(in_quotes),
				0) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		change_quote_state(in_quotes, get_current_quotes(in_quotes));
		temp->p_fast++;
		temp->p_slow = temp->p_fast;
		return (0);
	}
	return (UNCLOSED_QUOTES);
}
