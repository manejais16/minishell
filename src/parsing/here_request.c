/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:17:21 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/18 18:05:02 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*TODO: Add SIGINT catching for the readline!!!*/
int	ask_for_heredock_inputs(t_main *shell)
{
	t_heredoc	*iter;
	char		*input;
	char		*temp;

	iter = shell->p_here;
	input = NULL;
	while (iter)
	{
		input = readline(">");
		while(1)
		{
			if (ft_strcmp(input, iter->delimiter) == 0)
				break ;
			temp = ft_strjoin(input, iter->heredoc_input);
			if (!temp)
				return (free(input), -1);
			free(temp);
			input = readline(">");
		}
		iter = iter->next;
	}
	return (0);
}
