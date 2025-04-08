/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_meta_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:28:01 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/08 16:53:22 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_quotes(const char input)
{
	return (input == '\'' || input == '\"');
}

void	change_quote_state(int *state, const char input)
{
	int	quote_type;

	if (input == '\'')
		quote_type = SINGLE;
	else
		quote_type = DOUBLE;
	if (state[quote_type] == 1)
		state[quote_type] = 0;
	else
		state[quote_type] = 1;
	return ;
}
/*These are all meta characters*/
// int	is_meta_char(const char input)
// {
// 	if (input == '\'' || input == ' ' || input == '\t' || \
// 		input == '\n' || input == '|' || input == '&' || \
// 		input == ';' || input == '(' || input == ')' || \
// 		input == '<' || input == '>')
// 		return (1);
// 	else
// 		return (0);
// }

int	is_meta_char(const char input)
{
	if (input == ' ' || input == '|' || input == '&' || \
		input == '<' || input == '>')
		return (1);
	else
		return (0);
}

int	is_in_quotes(int in_quotes[2])
{
	return (in_quotes[0] || in_quotes[1]);
}

char	get_current_quotes(int int_quotes[2])
{
	return (int_quotes[SINGLE] * '\'' \
		+ int_quotes[DOUBLE] * '\"');
}
