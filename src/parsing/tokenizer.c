/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 08:58:43 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/01 09:01:09 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenize_input(char *input)
{
	return (ft_split(input, ' '));
}
void free_tokens(char **tokens)
{
	int i = 0;

	while(tokens[i])
		free(tokens[i++]);
	free(tokens);
}
