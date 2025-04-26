/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:04:34 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 14:50:23 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*handle_dollar_or_question(t_main *main, const char *str, \
			size_t *var_name_len)
{
	if (str[1] == '\0' || is_space_or_tab(str[1]))
	{
		*var_name_len = 0;
		return (handle_just_dollar());
	}
	if (str[1] == '?')
	{
		*var_name_len = 1;
		return (handle_exit_status(main));
	}
	return (NULL);
}

char	*get_expanded_value(t_main *main, const char *str, size_t *var_name_len)
{
	char	*var_name;
	char	*var_value;

	if (str[1] == '\0' || is_space_or_tab(str[1]) || str[1] == '?')
		return (handle_dollar_or_question(main, str, var_name_len));
	var_name = extract_var_name(str + 1);
	if (!var_name)
		return (NULL);
	*var_name_len = ft_strlen(var_name);
	if (*var_name_len == 0)
	{
		free(var_name);
		return (ft_strdup(""));
	}
	var_value = get_env_value(main->envp, var_name);
	if (!var_value)
		var_value = ft_strdup("");
	else
		var_value = ft_strdup(var_value);
	free(var_name);
	return (var_value);
}

char	*extract_var_name(const char *str)
{
	size_t	var_len;
	char	*var_name;

	if (!str)
		return (NULL);
	var_len = get_var_name_len(str);
	if (var_len == 0)
		return (ft_strdup(""));
	var_name = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, str, var_len + 1);
	return (var_name);
}

size_t	get_var_name_len(const char *str)
{
	size_t	len;

	len = 0;
	if (!str || !str[0])
		return (len);
	if (str[0] == '?')
		return (1);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}
