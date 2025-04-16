/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:02:22 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/16 16:04:18 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_and_expand_vars(t_main *main, char **expanded_str)
{
	size_t	i;
	bool	var_expanded;

	i = 0;
	var_expanded = false;
	while ((*expanded_str)[i])
	{
		if ((*expanded_str)[i] == '$')
		{
			if (expand_var_in_string(main, expanded_str, i))
			{
				var_expanded = true;
				continue ;
			}
		}
		i++;
	}
	return (var_expanded);
}

bool	expand_var_in_string(t_main *main, char **expanded_str, size_t i)
{
	char	*temp;

	if (!expanded_str || !*expanded_str || (*expanded_str)[i] != '$')
		return (false);
	temp = expand_var_at_pos(main, *expanded_str, i);
	if (!temp)
		return (false);
	free(*expanded_str);
	*expanded_str = temp;
	return (true);
}

char	*expand_var_at_pos(t_main *main, const char *str, size_t pos)
{
	char	*result;
	char	*var_value;
	size_t	var_name_len;
	char	*parts[2];

	if (!str || pos >= ft_strlen(str) || str[pos] != '$')
		return (ft_strdup(str));
	var_value = get_expanded_value(main, str + pos, &var_name_len);
	if (!var_value)
		return (ft_strdup(str));
	if (extract_string_parts(str, pos, var_name_len, parts) < 0)
	{
		free(var_value);
		return (ft_strdup(str));
	}
	result = ft_strjoin3(parts[0], var_value, parts[1]);
	free(parts[0]);
	free(parts[1]);
	free(var_value);
	return (result);
}

int	extract_string_parts(const char *str, size_t pos, size_t var_name_len,
		char **parts)
{
	parts[0] = ft_substr(str, 0, pos);
	parts[1] = ft_substr(str, pos + var_name_len + 1, ft_strlen(str) - pos
			- var_name_len - 1);
	if (!parts[0] || !parts[1])
	{
		free(parts[0]);
		free(parts[1]);
		return (-1);
	}
	return (0);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*result;
	char	*temp;

	if (!s1 || !s2 || !s3)
		return (NULL);
	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}
