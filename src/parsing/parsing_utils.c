/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:45:11 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/08 19:47:32 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*substr_dangeros(char const *s, unsigned int start, size_t len)
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
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}