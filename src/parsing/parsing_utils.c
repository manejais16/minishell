/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:45:11 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/09 15:50:02 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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