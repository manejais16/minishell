/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:45:11 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 15:28:22 by kzarins          ###   ########.fr       */
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
	return (in_quotes[SINGLE_Q] * 1 + in_quotes[DOUBLE_Q] * 2);
}

char	*ft_strjoin3_no_nullcheck(char const *s1, char const *s2, \
		char const *s3)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

int	is_space_or_tab(char input)
{
	return (input == ' ' || input == '\t');
}

void	print_fundamental_error(int ret_val)
{
	ft_putstr_fd("Minishell: There is malloc error!\n", STDERR_FILENO);
	ft_putstr_fd("Error NR.: ", STDERR_FILENO);
	ft_putnbr_fd(ret_val, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
