/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:57:17 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/24 11:11:20 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command_not_found(char **tokens, t_token *token_with_meta)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tokens[0], 2);
	ft_putstr_fd(" : command not found\n", 2);
	(void)tokens;
	g_exit_status = 127;
	close_redirections(token_with_meta);
}

char	**tokens_list_to_array(t_token *first_token)
{
	char	**tokens_array;
	int		count;
	t_token	*current;
	int		i;

	count = count_tokens_in_list(first_token);
	tokens_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tokens_array)
		return (NULL);
	i = 0;
	current = first_token;
	while (current)
	{
		tokens_array[i] = ft_strdup(current->str);
		if (!tokens_array[i])
		{
			shell_free_split(tokens_array);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	tokens_array[i] = NULL;
	return (tokens_array);
}

int	count_tokens_in_list(t_token *first_token)
{
	int		count;
	t_token	*current;

	count = 0;
	current = first_token;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
