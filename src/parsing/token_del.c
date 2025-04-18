/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:49:18 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/18 18:02:38 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	free_all_metachar(t_token *token)
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
	shell->last_token = NULL;
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

int	free_user_input(t_main *shell)
{
	t_heredoc	*temp;
	
	free_all_tokens(shell);
	if (shell->user_input)
		free(shell->user_input);
	while (shell->p_here)
	{
		if (shell->p_here->delimiter)
			free(shell->p_here->delimiter);
		if (shell->p_here->heredoc_input)
			free(shell->p_here->heredoc_input);
		temp = shell->p_here->next;
		free(shell->p_here);
		shell->p_here = temp;
	}
	return (0);
}