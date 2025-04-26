/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_extraction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:19:46 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 15:25:15 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	extract_meta_smaller(t_main *shell, t_twopointer *temp)
{
	temp->p_fast++;
	if (*temp->p_fast == '<')
	{
		if (add_token_at_end(shell, ft_strdup("<<"), NONE, 0) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_fast++;
	}
	else if (add_token_at_end(shell, ft_strdup("<"), NONE, 0) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	temp->p_slow = temp->p_fast;
	return (0);
}

int	extract_meta_larger(t_main *shell, t_twopointer *temp)
{
	temp->p_fast++;
	if (*temp->p_fast == '>')
	{
		if (add_token_at_end(shell, ft_strdup(">>"), NONE, 0) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_fast++;
	}
	else if (add_token_at_end(shell, ft_strdup(">"), NONE, 0) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	temp->p_slow = temp->p_fast;
	return (0);
}

int	extract_meta_token(t_main *shell, t_twopointer *temp)
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
