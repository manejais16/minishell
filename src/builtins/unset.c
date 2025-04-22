/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:04:13 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/22 14:22:16 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the given string is a valid environment variable name
int	is_valid_identifier(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// Checks if the given environment variable matches the provided name
int	is_matching_name(char *env_var, char *name)
{
	int	name_len;

	if (!env_var || !name)
		return (0);
	name_len = ft_strlen(name);
	if (ft_strncmp(env_var, name, name_len) != 0)
		return (0);
	if (env_var[name_len] != '=' && env_var[name_len] != '\0')
		return (0);
	return (1);
}

// Copies all environment variables that do not match the given name
// and frees the old environment variables
static int	cleanup_and_copy(char ***envp, char **new_env, char *name)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (!name)
		return (-1);
	while ((*envp)[++i])
	{
		if (!is_matching_name((*envp)[i], name))
		{
			new_env[j] = ft_strdup((*envp)[i]);
			if (!new_env[j])
			{
				while (j > 0)
					free(new_env[--j]);
				free(new_env);
				return (-1);
			}
			j++;
		}
	}
	new_env[j] = NULL;
	return (0);
}

// Removes the environment variable with the given name from the environment
int	remove_env_name(char ***envp, char *name)
{
	char	**new_env;
	int		len;
	int		result;

	if (!envp || !*envp || !name)
		return (-1);
	len = env_size(*envp);
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (-1);
	result = cleanup_and_copy(envp, new_env, name);
	if (result < 0)
		return (-1);
	shell_free_split(*envp);
	*envp = new_env;
	return (0);
}

// Unsets the environment variables specified by the tokens, printing an error
// if any of the tokens is not a valid identifier
int	ft_unset(char **tokens, t_main *shell)
{
	int	i;
	int	result;
	int	status;

	status = 0;
	i = 1;
	while (tokens[i])
	{
		if (tokens[i] && is_valid_identifier(tokens[i]))
		{
			result = remove_env_name(&shell->envp, tokens[i]);
			if (result < 0)
				return (1);
		}
		else
		{
			ft_putstr_fd("bash: unset: ", 2);
			ft_putstr_fd(tokens[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			status = 1;
		}
		i++;
	}
	return (status);
}
