/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:33:12 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/11 09:47:05 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static int	extract_meta_smaller(t_main *shell, t_twopointer *temp)
{
	temp->p_fast++;
	if (*temp->p_fast == '<')
	{
		if (add_token_at_end(shell, ft_strdup("<<"), NONE) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_fast++;
	}
	else
		if (add_token_at_end(shell, ft_strdup("<"), NONE) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	temp->p_slow = temp->p_fast;
	return (0);
}

static int	extract_meta_larger(t_main *shell, t_twopointer *temp)
{
	temp->p_fast++;
	if (*temp->p_fast == '>')
	{
		if (add_token_at_end(shell, ft_strdup(">>"), NONE) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_fast++;
	}
	else
		if (add_token_at_end(shell, ft_strdup(">"), NONE) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	temp->p_slow = temp->p_fast;
	return (0);
}

static int	extract_meta_token(t_main *shell, t_twopointer *temp)
{
	if (*temp->p_fast == '|')
	{
		if (add_token_at_end(shell, ft_strdup("|"), NONE) == MALLOC_FAIL)
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

static int	extract_token(t_main *shell, t_twopointer *temp)
{
	if (is_meta_char(*temp->p_fast) && *temp->p_fast != ' ')
	{
		if (extract_meta_token(shell, temp) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	else if (*temp->p_fast != ' ')
	{
		while (*temp->p_fast != ' ' && *temp->p_fast && \
			!is_quotes(*temp->p_fast) && !is_meta_char(*temp->p_fast))
			temp->p_fast++;
		if (add_token_at_end(shell, \
			substr_dangeros(temp->p_slow, temp->p_fast - temp->p_slow), \
			NONE) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_slow = temp->p_fast;
	}
	return (0);
}

int	extract_unquoted(t_main *shell, t_twopointer *temp, int *return_val)
{
	if (*temp->p_fast != ' ')
	{
		*return_val = extract_token(shell, temp);
		if (*return_val < 0)
			return (*return_val);
	}
	else
	{
		temp->p_fast++;
		temp->p_slow = temp->p_fast;
	}
	return (0);
}
