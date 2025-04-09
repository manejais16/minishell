/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:33:12 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/09 16:05:25 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
/*
static char	*next_token(const char *str, char c, int *k)
{
	char	*word;
	int		start;
	int		end;

	while (str[*k] && str[*k] == c)
		(*k)++;
	start = *k;
	while (str[*k] && str[*k] != c)
		(*k)++;
	end = *k;
	word = ft_substr(str, start, end - start);
	if (word == NULL)
		return (NULL);
	return (word);
}

static int	fill_split(char **result, const char *str, char c, int word_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < word_count)
	{
		result[i] = next_word(str, c, &j);
		if (result[i] == NULL)
		{
			free_split(result, i);
			return (0);
		}
		i++;
	}
	result[i] = NULL;
	return (1);
}

char	*split_tokens(const char *str, char c)
{
	char	**result;
	int		word_count;

	if (str == NULL)
		return (NULL);
	word_count = count_words(str, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (!fill_split(result, str, c, word_count))
		return (NULL);
	return (result);
}
*/
static int	get_token_quote_type(int *in_quotes)
{
	return (in_quotes[SINGLE_Q] * 1 \
		+ in_quotes[DOUBLE_Q] * 2);
}

static int	add_token_at_end(t_main *shell, t_token token)
{
	t_token	*temp_stor;
	t_token	*temp_iter;

	temp_stor = malloc(sizeof(t_token));
	if (!temp_stor)
		return (MALLOC_FAIL);
	temp_stor->str = token.str;
	temp_stor->quote_type = token.quote_type;
	temp_iter =  shell->first_token;
	shell->last_token = temp_stor;
	if (temp_iter == NULL)
	{
		shell->first_token = temp_stor;
		return (0);
	}
	while (temp_iter->next)
		temp_iter = temp_iter->next;
	temp_iter->next = temp_stor;
	temp_stor->prev = temp_iter;
	return (0);
}

static int	extract_quotes(t_main *shell, t_twopointer *temp, int *in_quotes)
{
	change_quote_state(in_quotes, *temp->p_fast);
	temp->p_slow++;
	temp->p_fast++;
	while (*temp->p_fast && *temp->p_fast != get_current_quotes(in_quotes))
		temp->p_fast++;
	if (*temp->p_fast)
	{
		if (add_token_at_end( shell, \
			(t_token) { .str = substr_dangeros(temp->p_slow, temp->p_fast - temp->p_slow), \
			.quote_type = get_token_quote_type(in_quotes)}) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		change_quote_state(in_quotes, get_current_quotes(in_quotes));
		temp->p_fast++;
		temp->p_slow = temp->p_fast;
		return (0);
	}
	return (UNCLOSED_QUOTES);
}

static int	extract_meta_token(t_main *shell, t_twopointer *temp)
{
	if (*temp->p_fast == '|')
	{
		if (add_token_at_end( shell, \
			(t_token) { .str = "|", .quote_type = NONE}) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_fast++;
		temp->p_slow = temp->p_fast;
	}
	else if (*temp->p_fast == '>')
	{
		temp->p_fast++;
		if (*temp->p_fast == '>')
		{
			if (add_token_at_end( shell, \
				(t_token) { .str = ">>", .quote_type = NONE}) == MALLOC_FAIL)
				return (MALLOC_FAIL);
			temp->p_fast++;
		}
		else
			if (add_token_at_end( shell, \
				(t_token) { .str = ">", .quote_type = NONE}) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		temp->p_slow = temp->p_fast;
	}
	else if (*temp->p_fast == '<')
	{
		temp->p_fast++;
		if (*temp->p_fast == '<')
		{
			if (add_token_at_end( shell, \
				(t_token) { .str = "<<", .quote_type = NONE}) == MALLOC_FAIL)
				return (MALLOC_FAIL);
			temp->p_fast++;
		}
		else
			if (add_token_at_end( shell, \
				(t_token) { .str = "<", .quote_type = NONE}) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		temp->p_slow = temp->p_fast;
	}
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
		while(*temp->p_fast != ' ' && *temp->p_fast && !is_quotes(*temp->p_fast))
			temp->p_fast++;
		if (add_token_at_end( shell, \
			(t_token) { .str = substr_dangeros(temp->p_slow, temp->p_fast - temp->p_slow), \
				.quote_type = NONE}) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		temp->p_slow = temp->p_fast;	
	}
	return (0);
}

//TODO: Still on development!!!
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
		else if (*temp.p_fast != ' ')
		{
			return_val = extract_token(shell, &temp);
			if (return_val < 0)
				return (return_val);
		}
		else
		{
			temp.p_fast++;
			temp.p_slow = temp.p_fast;
		}
	}
	return (0);
}
