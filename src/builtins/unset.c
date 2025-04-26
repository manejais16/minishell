/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:04:13 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 15:16:20 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
