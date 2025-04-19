/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 08:58:43 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/19 15:25:47 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/*TODO: Implement error messages for all fundamental
errors!*/
void	print_fundamental_error(int ret_val)
{
	(void)ret_val;
}

int extract_first_quote(t_main *shell, t_twopointer *temp)
{
	bool	is_compound;

	is_compound = 1;
	if (temp->p_fast == temp->p_slow)
		return (0);
	if (add_token_at_end(shell, \
		substr_dangeros(temp->p_slow, temp->p_fast - temp->p_slow), \
		NONE, is_compound) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	temp->p_slow = temp->p_fast;
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
		return_val = extract_first_quote(shell, &temp);
		if (return_val < 0)
			return (return_val);
	}
	return (0);
}

int	add_heredoc_in_linked_list(t_main *shell, t_heredoc *heredoc)
{
	t_heredoc	*iter;

	heredoc->next = NULL;
	iter = shell->p_here;
	if (!iter)
	{
		shell->p_here = heredoc;
		return (0);
	}
	while (iter->next)
		iter = iter->next;
	iter->next = heredoc;
	return (0);
}

int add_heredoc(t_main *shell, t_token *here_delimitor)
{
	t_heredoc	*temp;

	temp = malloc(sizeof(t_heredoc));
	if (!temp)
		return (MALLOC_FAIL);
	temp->delimiter = ft_strdup(here_delimitor->str);
	if (!temp->delimiter)
		return (free(temp), MALLOC_FAIL);
	if (here_delimitor->quote_type != NONE)
		temp->delimiter_quoted = 1;
	temp->already_used = 0;
	temp->heredoc_input = NULL;
	add_heredoc_in_linked_list(shell, temp);
	return (0);
}

int	reassign_meta_t(t_main *shell, t_token *token, t_token **start)
{
	t_token	*temp;
	
	if (add_meta_to_token(shell, token, get_meta_type((*start)->str), (*start)->next) == -1)
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

/*TODO: still have to expand the token if it is $var*/
int	assign_redirections_to_token(t_main *shell, t_token **current_t)
{
	t_token	temp;
	t_token	*first_cmd;

	first_cmd = NULL;
	initialize_token(&temp);
	while (*(*current_t)->str != '|')
	{
		if (is_meta_char(*(*current_t)->str) && *(*current_t)->str != ' ')
		{
			if (reassign_meta_t(shell, &temp, &(*current_t)) == -1)
				return (-1);
		}
		else
		{
			if (!first_cmd)
				first_cmd = (*current_t);
			(*current_t) = (*current_t)->next;
		}
		if ((*current_t) == NULL)
			break ;
	}
	if (first_cmd == NULL)
		return(dup_empty_str_token(shell, *current_t, &temp));
	first_cmd->meta = temp.meta;
	return (0);
}

/*TODO: must think of what happens when there is no tokens*/
int	assign_all_redirections(t_main	*shell)
{
	t_token	*temp;

	temp = shell->first_token;
	if (!temp)
		return (0);
	while (temp)
	{
		if (assign_redirections_to_token(shell, &temp) == -1)
			return (-1);
		if (temp == NULL)
			break;
		if (*temp->str == '|')
			temp = temp->next;
	}
	return (0);
}

/*TODO: Still have to set exit codes in case
it fails*/
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
	ret_val = assign_all_redirections(shell);
	if (ret_val != 0)
	{
		free_all_tokens(shell);
		/*TODO: If it fails there might be some malloc fail*/
		return (-1);
	}
	ask_for_heredock_inputs(shell);
	expand_variables(shell);
	return (0);
}
