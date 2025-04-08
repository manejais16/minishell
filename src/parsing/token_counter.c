/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 06:30:44 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/08 18:50:27 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "parsing.h"
#include "../../lib/libft/libft.h"

static int	count_quotes(const char **s, int *in_quotes, int *count)
{
	change_quote_state(in_quotes, **s);
	(*count)++;
	(*s)++;
	while (**s && **s != get_current_quotes(in_quotes))
		(*s)++;
	if (**s)
	{
		change_quote_state(in_quotes, get_current_quotes(in_quotes));
		(*s)++;
	}
	return (0);
}

static int	go_through_str(const char **s, int *in_quotes, int *count)
{
	if (is_quotes(**s) && !is_in_quotes(in_quotes))
		count_quotes(s, in_quotes, count);
	else if (is_meta_char(**s) && **s != ' ')
	{
		(*count)++;
		(*s)++;
	}
	else if (ft_isalnum(**s) || **s == '_')
	{
		while (ft_isalnum(**s) || **s == '_')
			(*s)++;
		(*count)++;
	}
	else if (**s == ' ')
		(*s)++;
	else
		return (ILEGAL_CHAR);
	return (0);
}

int	count_words(char const *s)
{
	int	count;
	int	in_quotes[2];

	count = 0;
	ft_memset(in_quotes, 0, sizeof(int) * 2);
	while (*s != '\0')
	{
		if (go_through_str(&s, in_quotes, &count) == ILEGAL_CHAR)
			return (ILEGAL_CHAR);
	}
	if (in_quotes[0] || in_quotes[1])
		return (UNCLOSED_QUOTES);
	return (count);
}
