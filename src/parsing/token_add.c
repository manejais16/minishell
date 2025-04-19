/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:03:31 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/19 13:58:11 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	initialize_token(t_token *token)
{
	token->str = NULL;
	token->quote_type = -1;
	token->prev = NULL;
	token->next = NULL;
	token->meta = NULL;
	token->is_compound_token = 0;
}

int	add_token_at_end(t_main *shell, char *str, int quote_type, bool is_comp)
{
	t_token	*temp_stor;
	t_token	*temp_iter;

	if (!str)
		return (MALLOC_FAIL);
	temp_stor = malloc(sizeof(t_token));
	if (!temp_stor)
		return (MALLOC_FAIL);
	initialize_token(temp_stor);
	temp_stor->str = str;
	temp_stor->quote_type = quote_type;
	temp_stor->is_compound_token = is_comp;
	temp_iter = shell->first_token;
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

int add_token_before(t_main *shell, t_token *token, t_token *new)
{
	if (!token)
	{
		new->prev = shell->last_token;
		shell->last_token = new;
		if (!shell->first_token)
			shell->first_token = new;
		new->next = NULL;
		return (0);
	}
	if (shell->first_token == token)
		shell->first_token = new;
	new->prev = token->prev;
	token->prev = new;
	new->next = token;
	return (0);
}

/*TODO: This should still be managed!*/
// int	add_token_after(t_main *shell, t_token *token, t_token *new)
// {
// 	if (shell->last_token == token)
// 		shell->last_token = new;
// 	new->next = token->next;
// 	token->next = new;
// 	new->prev = token;
// 	return (0);
// }

int	dup_empty_str_token(t_main *shell, t_token *current_token,\
		t_token *token_to_add)
{
	t_token	*temp;

	if (!token_to_add)
		return (-1);
	temp = malloc(sizeof(t_token));
	if (!temp)
		return (free_all_metachar(token_to_add), -1);
	initialize_token(temp);
	temp->str = ft_strdup("");
	if (!temp->str)
		return (free_all_metachar(token_to_add), free(temp), -1);
	temp->meta = token_to_add->meta;
	add_token_before(shell, current_token, temp);
	return (0);
}
