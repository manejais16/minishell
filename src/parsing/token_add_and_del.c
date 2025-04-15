/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_and_del.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:49:18 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/15 20:08:32 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	initialize_token(t_token *token)
{
	token->str = NULL;
	token->type = -1;
	token->quote_type = -1;
	token->var_exists = 0;
	token->prev = NULL;
	token->next = NULL;
	token->meta = NULL;
}

int	add_token_at_end(t_main *shell, char *str, int quote_type)
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

static int	free_all_metachar(t_token *token)
{
	while (token->meta)
	{
		if (token->meta->file_name != NULL)
		{
			free(token->meta->file_name);
		}
		free(token->meta);
		token->meta = token->meta->next;
	}
	token->meta = NULL;
	return (0);
}

int	free_all_tokens(t_main *shell)
{
	t_token *next;
	
	while(shell->first_token)
	{
		free_all_metachar(shell->first_token);
		free(shell->first_token->str);
		next = shell->first_token->next;
		free(shell->first_token);
		shell->first_token = next;
	}
	return (0);
}

int	free_one_token(t_token *token)
{
	free_all_metachar(token);
	free(token->str);
	free(token);
	token = NULL;
	return (0);
}