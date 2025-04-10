/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:45:11 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/10 19:46:31 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*substr_dangeros(char const *s, size_t len)
{
	char	*substr;

	if (s == NULL)
	{
		return (NULL);
	}
	substr = (char *)malloc(len + 1);
	if (substr == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(substr, s, len + 1);
	return (substr);
}

int	get_token_quote_type(int *in_quotes)
{
	return (in_quotes[SINGLE_Q] * 1 \
		+ in_quotes[DOUBLE_Q] * 2);
}
