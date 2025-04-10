/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_and_del.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:49:18 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/10 20:08:30 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	add_token_at_end(t_main *shell, char *str, int quote_type)
{
	t_token	*temp_stor;
	t_token	*temp_iter;

	if (!str)
		return (MALLOC_FAIL);
	temp_stor = malloc(sizeof(t_token));
	if (!temp_stor)
		return (MALLOC_FAIL);
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

/*TODO: make a function that frees all tokens!*/
int	free_all_tokens(t_main *shell)
{
	(void)shell;
}