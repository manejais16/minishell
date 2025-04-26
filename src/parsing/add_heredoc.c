/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:55:53 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 16:32:24 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	add_heredoc(t_main *shell, t_token *here_delimitor)
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

int	is_heredoc_token(t_token *token)
{
	char	*temp;

	if (!token)
		return (0);
	if (!token->str)
		return (0);
	temp = token->str;
	if (*temp == '<' && *(temp + 1) == '<' && token->quote_type == NONE)
		return (1);
	return (0);
}
