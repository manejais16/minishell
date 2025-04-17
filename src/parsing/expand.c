/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:34:03 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/17 15:52:58 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_token_expansion(t_token *token)
{
	char	*expanded_str;

	if (!token || !token->str)
		return (NULL);
	if (token->quote_type == SINGLE)
		return (NULL);
	expanded_str = ft_strdup(token->str);
	if (!expanded_str)
		return (NULL);
	return (expanded_str);
}

int	expand_variables_in_token(t_main *main, t_token *token)
{
	char	*expanded_str;
	int		result;

	expanded_str = init_token_expansion(token);
	if (!expanded_str)
	{
		if (token && token->quote_type == SINGLE)
			return (0);
		return (-1);
	}
	result = perform_token_expansion(main, token, &expanded_str);
	return (result);
}

int	expand_variables(t_main *main)
{
	t_token	*current;
	int		ret;

	if (!main || !main->first_token)
		return (0);
	current = main->first_token;
	while (current)
	{
		ret = expand_variables_in_token(main, current);
		if (ret < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

int	perform_token_expansion(t_main *main, t_token *token, char **expanded_str)
{
	bool	var_expanded;
	bool	tilde_expanded;

	if (!expanded_str || !*expanded_str)
		return (-1);
	tilde_expanded = false;
	if (token->quote_type == NONE && (*expanded_str)[0] == '~')
		tilde_expanded = expand_tilde_in_string(main, expanded_str);
	var_expanded = find_and_expand_vars(main, expanded_str);
	free(token->str);
	token->str = *expanded_str;
	token->var_exists = var_expanded || tilde_expanded;
	return (0);
}

bool	expand_tilde_in_string(t_main *main, char **str)
{
	char	*home_value;
	char	*new_str;

	if (!str || !*str || (*str)[0] != '~')
		return (false);
	home_value = get_env_value(main->envp, "HOME");
	if (!home_value)
		return (false);
	if ((*str)[1] == '\0' || (*str)[1] == '/')
	{
		new_str = ft_strjoin(home_value, (*str) + 1);
		if (!new_str)
			return (false);
		free(*str);
		*str = new_str;
		return (true);
	}
	return (false);
}
