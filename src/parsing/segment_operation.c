/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:11:37 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/22 20:09:12 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static int	extract_segment(t_main *shell, t_twopointer *temp)
{
		while (*temp->p_fast && !is_quotes(*temp->p_fast))
			temp->p_fast++;
		if (add_token_at_end(shell, \
			substr_dangeros(temp->p_slow, temp->p_fast - temp->p_slow), \
			NONE, 0) == MALLOC_FAIL)
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
	expand_variables_in_token(real_shell, &temp);
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
		find_and_expand_vars(real_shell, &expanded_str);
		if (!expanded_str)
			return (-1);
		free(temp->str);
		temp->str = expanded_str;
		temp = temp->next;
	}
	return (0);
}

int	combine_in_one_token(t_token *token, t_main	*temp_shell)
{
	char	*result;
	t_token	*walker;

	walker = temp_shell->first_token;
	free(token->str);
	token->str = NULL;
	while (walker)
	{
		if (ft_strcmp("$", walker->str) == 0 && walker->next && \
			!is_heredoc_token(token->prev))
		{
			walker = walker->next;
			continue ;
		}
		token->str = ft_strjoin(result, walker->str);
		if (!token->str)
			return (free(result), MALLOC_FAIL);
		result = token->str;
		walker = walker->next;
	}
	token->quote_type = SINGLE;
	token->is_compound_token = 0;
	return (0);
}

// int	replace_token(t_main *shell, t_main *temp_shell, t_token **token)
// {
// 	/*I am here!!!!!!!!!!!!!!!!!!!!!!!!*/
// 	free (*token);
// 	*token = temp_shell->last_token;
// }

int	go_through_segment(t_main *shell, t_token **token)
{
	t_main			temp_shell;
	t_twopointer	temp;
	int				in_quotes[2];
	int				return_val;

	init_terminal_variables(&temp_shell);
	temp_shell.user_input = (*token)->str;
	temp.p_fast = temp_shell.user_input;
	temp.p_slow = temp.p_fast;
	ft_memset(in_quotes, 0, sizeof(int) * 2);
	while (*temp.p_fast)
	{
		if (is_quotes(*temp.p_fast) && !is_in_quotes(in_quotes))
		{
			return_val = extract_quote_segment(&temp_shell, &temp, in_quotes);
			if (return_val < 0)
				return (free_all_tokens(&temp_shell), return_val);
		}
		else
		{
			return_val = extract_unquoted_segment(&temp_shell, &temp, &return_val);
			if (return_val < 0)
				return (free_all_tokens(&temp_shell), return_val);
		}
	}
	if (!is_heredoc_token((*token)->prev))
	{
		/*This is only if there is no heredoc before!!!*/
		expand_all_segments(shell, &temp_shell);
		//replace_token(shell, &temp_shell, token);
	}
	else
	{
		if (combine_in_one_token((*token), &temp_shell) == MALLOC_FAIL)
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
			if (go_through_segment(shell, &iter) != 0)
			{
				return (-1);
			}
		}
		iter = iter->next;
	}
	return (0);
}