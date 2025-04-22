/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   between_token_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:44:17 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/22 18:23:49 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	remove_token_from_chain(t_main *shell, t_token *token)
{
	if (token->prev)
	{
		token->prev->next = token->next;
		if (token->next)
			token->next->prev = token->prev;
	}
	else if (token->next)
		token->next->prev = NULL;
	if (shell->first_token == token && shell->last_token == token)
	{
		shell->first_token = NULL;
		shell->last_token = NULL;
	}
	if (!token->next)
	shell->last_token = token->prev;
	if (!token->prev)
	shell->first_token = token->next;
	free_one_token(token);
	return (0);
}

/*Evoke only after expansino is done*/
int	add_meta_to_token(t_main *shell, t_token *main_token, t_type meta_type, t_token *pseudo_t)
{
	t_metachar	*last_meta;
	t_metachar	*temp;

	temp = malloc(sizeof(t_metachar));
	if (!temp)
		return (-1);
	temp->file_name = ft_strdup(pseudo_t->str);
	if (!temp->file_name)
		return (free(temp), -1);
	if (meta_type != D_SMALLER && pseudo_t->quote_type != SINGLE)
		if (expand_string(shell, &temp->file_name) == -1)
			return (-1);
	temp->type = meta_type;
	temp->next = NULL;
	last_meta = main_token->meta;
	if (!last_meta)
	{
		main_token->meta = temp;
		return (0);
	}
	while (last_meta->next)
		last_meta = last_meta->next;
	last_meta->next = temp;
	return (0);
}

t_type	get_meta_type(char *token)
{
	if (*token == '>')
	{
		if (*(token + 1) == '\0')
			return (LARGER);
		return (D_LARGER);
	}
	if (*token == '<')
	{
		if (*(token + 1) == '\0')
			return (SMALLER);
		return (D_SMALLER);
	}
	if (*token == '|')
		return (PIPE);
	return (NONE_T);
}

/*BE CAREFUL!!!! the meta linked list does not get dublicated!!!*/
t_token	*token_dup(t_token *token)
{
	t_token	*result;

	result = malloc(sizeof(token));
	if (!result)
		return (NULL);
	initialize_token(result);
	result->str = ft_strdup(token->str);
	if (!result->str)
	{
		free (result);
		return (NULL);
	}
	result->prev = token->prev;
	result->next = token->next;
	result->meta = token->meta;
	token->meta = NULL;
	return (result);
}
