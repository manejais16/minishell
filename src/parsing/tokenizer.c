/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 08:58:43 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 16:24:23 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	extract_compound_token(t_main *shell, t_twopointer *temp, int *ret_val)
{
	bool	is_compound;

	is_compound = 1;
	if (temp->p_fast == temp->p_slow)
	{
		*ret_val = 0;
		return (0);
	}
	if (add_token_at_end(shell, substr_dangeros(temp->p_slow, temp->p_fast
				- temp->p_slow), NONE, is_compound) == MALLOC_FAIL)
	{
		*ret_val = MALLOC_FAIL;
		return (MALLOC_FAIL);
	}
	temp->p_slow = temp->p_fast;
	*ret_val = 0;
	return (0);
}

int	go_through_str(t_main *shell)
{
	t_twopointer	temp;
	int				in_quotes[2];
	int				return_val;

	temp.p_fast = shell->user_input;
	temp.p_slow = temp.p_fast;
	ft_memset(in_quotes, 0, sizeof(int) * 2);
	while (*temp.p_fast)
	{
		if (is_quotes(*temp.p_fast) && !is_in_quotes(in_quotes))
		{
			return_val = extract_quotes(shell, &temp, in_quotes);
			if (return_val < 0)
				return (return_val);
		}
		else
		{
			return_val = extract_unquoted(shell, &temp, in_quotes);
			if (return_val < 0)
				return (return_val);
		}
		if (extract_compound_token(shell, &temp, &return_val) < 0)
			return (return_val);
	}
	return (0);
}

int	reassign_meta_t(t_main *shell, t_token *token, t_token **start)
{
	t_token	*temp;

	if (add_meta_to_token(shell, token, get_meta_type((*start)->str),
			(*start)->next) == -1)
		return (-1);
	temp = (*start)->next->next;
	if (shell->first_token == *start)
		shell->first_token = temp;
	if (shell->last_token == (*start)->next)
		shell->last_token = (*start)->prev;
	if (get_meta_type((*start)->str) == D_SMALLER)
		if (add_heredoc(shell, (*start)->next) != 0)
			return (-1);
	remove_token_from_chain((*start)->next);
	remove_token_from_chain(*start);
	*start = temp;
	return (0);
}

int	extract_redirections(t_main *shell, t_token **current_t, \
	t_token *temp, t_token **first_cmd)
{
	if (is_meta_char(*(*current_t)->str) && \
	!is_space_or_tab(*(*current_t)->str) && \
	(*current_t)->quote_type == NONE)
	{
		if (reassign_meta_t(shell, temp, &(*current_t)) == -1)
			return (-1);
	}
	else
	{
		if (!*first_cmd)
			*first_cmd = (*current_t);
		(*current_t) = (*current_t)->next;
	}
	return (0);
}

int	tokenize_input(t_main *shell)
{
	int	ret_val;

	ret_val = go_through_str(shell);
	if (ret_val != 0)
	{
		free_all_tokens(shell);
		print_fundamental_error(ret_val);
		return (-1);
	}
	ret_val = check_for_repeating_meta(shell);
	if (ret_val != 0)
		return (free_all_tokens(shell), -1);
	ret_val = expand_compound_tokens(shell);
	if (ret_val != 0)
		return (free_all_tokens(shell), -1);
	ret_val = assign_all_redirections(shell);
	if (ret_val != 0)
		return (free_all_tokens(shell), -1);
	ask_for_heredock_inputs(shell);
	expand_all_heredocs(shell);
	expand_variables(shell);
	return (0);
}
