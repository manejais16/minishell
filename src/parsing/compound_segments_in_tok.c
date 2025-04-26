/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_segments_in_tok.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:36:59 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 16:59:30 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	combine_in_one_token_meta(t_token *token, t_main *temp_shell)
{
	char	*result;
	t_token	*walker;

	walker = temp_shell->first_token;
	free(token->str);
	token->str = NULL;
	while (walker)
	{
		if (ft_strcmp("$", walker->str) == 0 && walker->next
			&& !is_heredoc_token(token->prev))
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

int	add_one_char(char **input, char to_add)
{
	char	*result;
	int		len;

	len = ft_strlen(*input);
	result = malloc(len + 2);
	if (!result)
		return (MALLOC_FAIL);
	result = ft_strcpy(result, *input);
	result[len] = to_add;
	result[len + 1] = 0;
	free(*input);
	*input = result;
	return (0);
}

int	add_unenclosed_chars(t_token *walker, char **result, t_token **token_chain)
{
	int	walker_internal;

	walker_internal = 0;
	while (*(walker->str + walker_internal))
	{
		while (!is_space_or_tab(*(walker->str + walker_internal))
			&& *(walker->str + walker_internal) != '\0')
		{
			if (add_one_char(result, *(walker->str
						+ walker_internal)) != 0)
				return (MALLOC_FAIL);
			walker_internal++;
		}
		if (*(walker->str + walker_internal) == '\0')
			break ;
		if (is_space_or_tab(*(walker->str + walker_internal)) && *result)
		{
			add_result_to_chain(token_chain, *result);
			*result = NULL;
		}
		walker_internal++;
	}
	return (0);
}

int	append_link_to_result(t_token *walker, char **result, t_token **token_chain)
{
	char	*temp;

	if (walker->quote_type != NONE)
	{
		temp = ft_strjoin(*result, walker->str);
		if (!temp)
		{
			if (*result)
				free(*result);
			return (MALLOC_FAIL);
		}
		*result = temp;
	}
	else
	{
		if (add_unenclosed_chars(walker, result, token_chain) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	return (0);
}

int	combine_in_one_token_regular(t_token *token, t_main *temp_shell)
{
	t_token	*walker;
	t_token	*token_chain;
	char	*result;

	walker = temp_shell->first_token;
	result = NULL;
	token_chain = NULL;
	while (walker)
	{
		if (append_link_to_result(walker, &result, &token_chain) != 0)
			return (MALLOC_FAIL);
		walker = walker->next;
	}
	if (result)
		add_result_to_chain(&token_chain, result);
	replace_token_with_chain(token, token_chain);
	free_chain(token_chain);
	return (0);
}
