/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_chain_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:16:07 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 17:48:51 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	add_result_to_chain(t_token **chain, char *result)
{
	t_token	*link;
	t_token	*iter;

	link = malloc(sizeof(t_token));
	if (!link)
		return (-1);
	initialize_token(link);
	link->quote_type = SINGLE;
	link->str = result;
	if (!*chain)
	{
		*chain = link;
		return (0);
	}
	iter = *chain;
	while (iter->next)
		iter = iter->next;
	link->prev = iter;
	iter->next = link;
	return (0);
}

static void	inset_chain_in_token_list(t_token *token, t_token *chain)
{
	t_token	*temp;
	t_token	*iter;

	iter = chain;
	token->str = chain->str;
	chain->str = NULL;
	temp = token->next;
	while (iter->next)
		iter = iter->next;
	if (temp && chain->next)
	{
		temp->prev = iter;
		iter->next = temp;
	}
	if (chain->next)
	{
		token->next = chain->next;
		token->next->prev = token;
	}
}

int	replace_token_with_chain(t_token *token, t_token *chain)
{
	free(token->str);
	token->quote_type = SINGLE;
	token->str = NULL;
	if (chain)
		inset_chain_in_token_list(token, chain);
	else
	{
		token->str = ft_strdup("");
		if (!token->str)
			return (MALLOC_FAIL);
	}
	return (0);
}

int	free_chain(t_token *token_chain)
{
	if (token_chain)
		free(token_chain);
	token_chain = NULL;
	return (0);
}
