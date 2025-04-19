/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:11:37 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/19 21:35:21 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"


/*TODO: Everything in this file will have to get reconected*/
static int	extract_segment(t_main *shell, t_twopointer *temp)
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
			NONE, 0) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_slow = temp->p_fast;
	}
	return (0);
}

int	extract_unquoted_segment(t_main *shell, t_twopointer *temp, int *return_val)
{
	if (*temp->p_fast != ' ')
	{
		*return_val = extract_segment(shell, temp);
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

int	extract_quote_segment(t_main *shell, t_twopointer *temp, int *in_quotes)
{
	change_quote_state(in_quotes, *temp->p_fast);
	temp->p_slow++;
	temp->p_fast++;
	while (*temp->p_fast && *temp->p_fast != get_current_quotes(in_quotes))
		temp->p_fast++;
	if (*temp->p_fast)
	{
		if (add_token_at_end(shell, substr_dangeros(temp->p_slow, \
			temp->p_fast - temp->p_slow), get_token_quote_type(in_quotes),0) \
			== MALLOC_FAIL)
			return (MALLOC_FAIL);
		change_quote_state(in_quotes, get_current_quotes(in_quotes));
		temp->p_fast++;
		temp->p_slow = temp->p_fast;
		return (0);
	}
	return (UNCLOSED_QUOTES);
}

int	is_heredoc_token(t_token *token)
{
	char	*temp;
	
	if (!token)
		return (0);
	if (!token->str)
		return (0);
	temp = token->str;
	if (*temp == '>' && *(temp + 1) == '>' && token->quote_type == NONE)
		return (1);
	return (0);
}

int	expand_all_segments(t_main *real_shell, t_main *temp_shell)
{
	t_token	*temp;
	char	*expanded_str;
	
	temp = temp_shell->first_token;
	/*TODO: return value should be checked!!!!*/
	expand_variables_in_token(temp_shell, temp);
	temp = temp->next;
	while(temp)
	{
		expanded_str = init_token_expansion(temp);
		if (!expanded_str)
		{
			if (temp && temp->quote_type == SINGLE)
			{
				temp = temp->next;
				continue ;
			}
			return (-1);
		}
		find_and_expand_vars(real_shell, expanded_str);
		if (!expanded_str)
		return (-1);
		free(temp->str);
		temp->str = expanded_str;
		temp = temp->next;
	}
}

/*TODO: Combine everything in one token*/
int	combine_in_one_token(t_token *token, t_main	*temp_shell)
{
	(void)token;
	(void)temp_shell;
	return (0);
}

/*TODO: rewrite*/
/*Have to check if the segment before was not heredoc*/
int	go_through_segment(t_main *shell, t_token *token)
{
	t_main			temp_shell;
	t_twopointer	temp;
	int				in_quotes[2];
	int				return_val;

	init_terminal_variables(&temp_shell);
	temp_shell.user_input = token->str;
	temp.p_fast = temp_shell.user_input;
	temp.p_slow = temp.p_fast;
	ft_memset(in_quotes, 0, sizeof(int) * 2);
	while (*temp.p_fast)
	{
		if (is_quotes(*temp.p_fast) && !is_in_quotes(in_quotes))
		{
			return_val = extract_quote_segment(&temp_shell, &temp, in_quotes);
			if (return_val < 0)
				return (return_val);
		}
		else
		{
			return_val = extract_unquoted_segment(&temp_shell, &temp, &return_val);
			if (return_val < 0)
				return (return_val);
		}
	}
	if (!is_heredoc_token(token->prev))
	{
		expand_all_segments(shell, &temp_shell);
	}
	if (combine_in_one_token(token, &temp_shell) == MALLOC_FAIL)
		return (free_all_tokens(&temp_shell), MALLOC_FAIL);
	free_all_tokens(&temp_shell);
	return (0);
}
