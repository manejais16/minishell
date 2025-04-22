/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:34:03 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/22 19:19:41 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

/*TODO: the expanded_str will leak if the result will be 
-1, because it will not be freed from init_token*/
int	expand_variables_in_token(t_main *main, t_token **token)
{
	char	*expanded_str;
	int		result;

	expanded_str = init_token_expansion(*token);
	if (!expanded_str)
	{
		if (*token && (*token)->quote_type == SINGLE)
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
		ret = expand_variables_in_token(main, &current);
		if (ret < 0)
			return (-1);
		current = current->next;
		/*There is a fault*/
	}
	return (0);
}

int	expand_tilde_in_string(t_main *main, char **str)
{
	char	*home_value;
	char	*new_str;

	if (!str || !*str || (*str)[0] != '~')
		return (0);
	home_value = get_env_value(main->envp, "HOME");
	if (!home_value)
		return (0);
	if ((*str)[1] == '\0' || (*str)[1] == '/')
	{
		new_str = ft_strjoin(home_value, (*str) + 1);
		if (!new_str)
			return (-1);
		free(*str);
		*str = new_str;
		return (1);
	}
	return (0);
}
/*wow*/
int	dup_token(t_token **new, t_token *old)
{
	if (*new)
		free_one_token(*new);
	*new = malloc(sizeof(t_token));
	if (!*new)
		return (-1);
	initialize_token(*new);
	(*new)->str = ft_strdup(old->str);
	if (!(*new)->str)
		return (-1);
	(*new)->is_compound_token = old->is_compound_token;
	(*new)->quote_type = old->quote_type;
	(*new)->var_exists = old->var_exists;
	return (0);
}

int	split_in_token_expansion(t_main *shell, t_token **token, char **expand_str)
{
	char **temp;
	t_token	*new;

	temp = ft_split(*expand_str, ' ');
	if (!temp)
		return (-1);
	new = NULL;
	while (*temp)
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return (-1);
		initialize_token(new);
		new->quote_type = SINGLE;
		new->str = ft_strdup(*temp);
		if (!new->str)
			return (free(new), -1);
		add_token_before(shell, *token, new);
		temp++;
	}
	// if (dup_token(token, new) != 0)
	// 	return (-1);
	// add_token_before(shell, new, *token);
	// ft_printf("%p\n", new->next);
	// remove_token_from_chain(shell, new);
	if (!new)
	{
		if ((*token)->str)
			free((*token)->str);
		(*token)->str = ft_strdup("");
		(*token)->quote_type = SINGLE;
	}
	else
	{
	remove_token_from_chain(shell, *token);
	*token = new;
	}
	free(*expand_str);
	*expand_str = NULL;
	return (0);
}

int	perform_token_expansion(t_main *main, t_token **token, char **expanded_str)
{
	int		tilde_result;
	bool	var_expanded;
	//t_token **print = token;

	if (!expanded_str || !*expanded_str)
		return (-1);
	tilde_result = 0;
	if ((*token)->quote_type == NONE && (*expanded_str)[0] == '~')
	{
		tilde_result = expand_tilde_in_string(main, expanded_str);
		if (tilde_result == -1)
			return (-1);
	}
	var_expanded = find_and_expand_vars(main, expanded_str);
	if (!*expanded_str)
		return (-1);
	free((*token)->str);
	if ((*token)->quote_type == DOUBLE)
	{
		(*token)->str = *expanded_str;
	}
	else
		split_in_token_expansion(main, token, expanded_str);
	(*token)->var_exists = var_expanded || (tilde_result == 1);
	return (0);
}
