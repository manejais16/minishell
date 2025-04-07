/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 08:58:43 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/07 12:07:01 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenize_input(char *input)
{
	return (ft_split(input, ' '));
}

/*TODO: Rewrite token freeing function to
work with t_token linked list*/
void free_tokens(char **tokens)
{
	int i = 0;

	while(tokens[i])
		free(tokens[i++]);
	free(tokens);
}
