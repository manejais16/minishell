/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:11:37 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 18:06:46 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	expand_subsequent_segments(t_main *real_shell, t_token **temp, \
	char **expanded_str)
{
	*expanded_str = init_token_expansion(*temp);
	if (!*expanded_str)
	{
		if (*temp && (*temp)->quote_type == SINGLE)
		{
			*temp = (*temp)->next;
			return (0);
		}
		return (-1);
	}
	if (ft_strcmp((*temp)->str, "$") == 0 && (*temp)->next)
		*expanded_str = strdup("");
	else
		find_and_expand_vars(real_shell, expanded_str);
	if (!*expanded_str)
		return (-1);
	free((*temp)->str);
	(*temp)->str = *expanded_str;
	*temp = (*temp)->next;
	return (0);
}

int	expand_all_segments(t_main *real_shell, t_main *temp_shell)
{
	t_token	*temp;
	char	*expanded_str;

	temp = temp_shell->first_token;
	if (ft_strcmp(temp->str, "$") == 0 && temp->next
		&& temp->quote_type == NONE)
	{
		expanded_str = strdup("");
		if (!expanded_str)
			return (-1);
		free(temp->str);
		temp->str = expanded_str;
	}
	else
		expand_variables_in_token(real_shell, temp);
	temp = temp->next;
	while (temp)
	{
		if (expand_subsequent_segments(real_shell, &temp, &expanded_str) != 0)
			return (MALLOC_FAIL);
	}
	return (0);
}

int	make_segment_tokens(t_main *temp_shell)
{
	t_twopointer	temp;
	int				in_quotes[2];
	int				return_val;

	ft_memset(in_quotes, 0, sizeof(int) * 2);
	temp.p_fast = temp_shell->user_input;
	temp.p_slow = temp.p_fast;
	while (*temp.p_fast)
	{
		if (is_quotes(*temp.p_fast) && !is_in_quotes(in_quotes))
		{
			return_val = extract_quote_segment(temp_shell, &temp, in_quotes);
			if (return_val < 0)
				return (free_all_tokens(temp_shell), return_val);
		}
		else
		{
			return_val = extract_unquoted_segment(temp_shell, &temp,
					&return_val);
			if (return_val < 0)
				return (free_all_tokens(temp_shell), return_val);
		}
	}
	return (0);
}

int	go_through_segment(t_main *shell, t_token *token)
{
	t_main			temp_shell;

	init_terminal_variables(&temp_shell);
	temp_shell.user_input = token->str;
	if (make_segment_tokens(&temp_shell) != 0)
		return (-1);
	if (!is_heredoc_token(token->prev))
	{
		expand_all_segments(shell, &temp_shell);
		if (combine_in_one_token_regular(token, &temp_shell) == MALLOC_FAIL)
			return (free_all_tokens(&temp_shell), MALLOC_FAIL);
	}
	else
	{
		if (combine_in_one_token_meta(token, &temp_shell) == MALLOC_FAIL)
			return (free_all_tokens(&temp_shell), MALLOC_FAIL);
	}
	free_all_tokens(&temp_shell);
	return (0);
}

int	expand_compound_tokens(t_main *shell)
{
	t_token	*iter;

	iter = shell->first_token;
	while (iter)
	{
		if (iter->is_compound_token)
		{
			if (go_through_segment(shell, iter) != 0)
			{
				return (-1);
			}
		}
		iter = iter->next;
	}
	return (0);
}
