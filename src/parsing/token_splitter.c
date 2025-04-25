/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:33:12 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/24 21:18:45 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static int	extract_meta_smaller(t_main *shell, t_twopointer *temp)
{
	temp->p_fast++;
	if (*temp->p_fast == '<')
	{
		if (add_token_at_end(shell, ft_strdup("<<"), NONE, 0) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_fast++;
	}
	else
		if (add_token_at_end(shell, ft_strdup("<"), NONE, 0) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	temp->p_slow = temp->p_fast;
	return (0);
}

static int	extract_meta_larger(t_main *shell, t_twopointer *temp)
{
	temp->p_fast++;
	if (*temp->p_fast == '>')
	{
		if (add_token_at_end(shell, ft_strdup(">>"), NONE, 0) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_fast++;
	}
	else
		if (add_token_at_end(shell, ft_strdup(">"), NONE, 0) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	temp->p_slow = temp->p_fast;
	return (0);
}

static int	extract_meta_token(t_main *shell, t_twopointer *temp)
{
	if (*temp->p_fast == '|')
	{
		if (add_token_at_end(shell, ft_strdup("|"), NONE, 0) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_fast++;
		temp->p_slow = temp->p_fast;
	}
	else if (*temp->p_fast == '>')
		extract_meta_larger(shell, temp);
	else if (*temp->p_fast == '<')
		extract_meta_smaller(shell, temp);
	return (0);
}

static int	extract_token(t_main *shell, t_twopointer *temp, int *in_quotes)
{
	bool	is_compound;
	int		ret_val;

	is_compound = 0;
	ret_val = 0;
	if (is_meta_char(*temp->p_fast) && !is_space_or_tab(*temp->p_fast))
	{
		if (extract_meta_token(shell, temp) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	else if (!is_space_or_tab(*temp->p_fast))
	{
		while (!is_space_or_tab(*temp->p_fast) && *temp->p_fast && \
			!is_meta_char(*temp->p_fast))
		{
			if (*temp->p_fast == '$' /*&& temp->p_fast != temp->p_slow*/)
				is_compound = 1;
			if (is_quotes(*temp->p_fast))
			{
				is_compound = 1;
				ret_val = extract_quotes(shell, temp, in_quotes);
			}
			else
				temp->p_fast++;
		}
		if (add_token_at_end(shell, \
			substr_dangeros(temp->p_slow, temp->p_fast - temp->p_slow), \
			NONE, is_compound) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_slow = temp->p_fast;
	}
	return (ret_val);
}

int	extract_unquoted(t_main *shell, t_twopointer *temp, int *is_quotes)
{
	int	ret_val;
	if (!is_space_or_tab(*temp->p_fast))
	{
		ret_val = extract_token(shell, temp, is_quotes);
		if (ret_val < 0)
			return (ret_val);
	}
	else
	{
		temp->p_fast++;
		temp->p_slow = temp->p_fast;
	}
	return (0);
}
