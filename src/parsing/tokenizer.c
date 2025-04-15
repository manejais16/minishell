/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 08:58:43 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/15 20:36:39 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/*Rewrite for our builtin struct*/
char	**tokenize_input(char *input)
{
	return (ft_split(input, ' '));
}

/*TODO: Remove when all the functions are overwritten*/
void	free_tokens(char **tokens)
{
	int	i = 0;

	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

int	go_through_str(t_main *shell)
{
	t_twopointer	temp;
	int				in_quotes[2];
	int				return_val;

	temp.p_fast = shell->user_input;
	temp.p_slow = temp.p_fast;
	ft_memset(in_quotes, 0, sizeof(int) * 2);
	while (*temp.p_fast)
	{
		if (is_quotes(*temp.p_fast) && !is_in_quotes(in_quotes))
		{
			return_val = extract_quotes(shell, &temp, in_quotes);
			if (return_val < 0)
				return (return_val);
		}
		else
		{
			return_val = extract_unquoted(shell, &temp, &return_val);
			if (return_val < 0)
				return (return_val);
		}
	}
	return (0);
}

// int assign_redirections_to_tokens(t_main *shell, t_token *start)
// {
// 	t_token	*temp;
// 	t_token	*nextp;
	
// 	/*TODO: still have to expand the token if it is $var*/

	
// 	//current = start;
// 	// while(current != shell->last_token)
// 	// {
// 	// 	if(current)
// 	// }
// }
