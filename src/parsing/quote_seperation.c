/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_seperation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:53:23 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/10 20:00:25 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	extract_quotes(t_main *shell, t_twopointer *temp, int *in_quotes)
{
	change_quote_state(in_quotes, *temp->p_fast);
	temp->p_slow++;
	temp->p_fast++;
	while (*temp->p_fast && *temp->p_fast != get_current_quotes(in_quotes))
		temp->p_fast++;
	if (*temp->p_fast)
	{
		if (add_token_at_end(shell, substr_dangeros(temp->p_slow, \
			temp->p_fast - temp->p_slow), get_token_quote_type(in_quotes)) \
			== MALLOC_FAIL)
			return (MALLOC_FAIL);
		change_quote_state(in_quotes, get_current_quotes(in_quotes));
		temp->p_fast++;
		temp->p_slow = temp->p_fast;
		return (0);
	}
	return (UNCLOSED_QUOTES);
}
