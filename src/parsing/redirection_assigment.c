/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_assigment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:07:09 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 16:08:45 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	assign_redirections_to_token(t_main *shell, t_token **current_t)
{
	t_token	temp;
	t_token	*first_cmd;

	first_cmd = NULL;
	initialize_token(&temp);
	while (*(*current_t)->str != '|')
	{
		extract_redirections(shell, current_t, &temp, &first_cmd);
		if ((*current_t) == NULL)
			break ;
	}
	if (first_cmd == NULL)
		return (dup_empty_str_token(shell, *current_t, &temp));
	first_cmd->meta = temp.meta;
	return (0);
}

int	assign_all_redirections(t_main *shell)
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
			break ;
		if (*temp->str == '|')
			temp = temp->next;
	}
	return (0);
}
