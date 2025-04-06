/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 09:04:13 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/06 16:09:20 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}
int	is_matching_key(char *env_var, char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (!env_var)
		return (0);
	if (ft_strncmp(env_var, key, key_len) != 0)
		return (0);
	if (env_var[key_len] != '=')
		return (0);
	return (1);
}

/*TODO: Give signal if the new_env malloc fails,
because the value will still be set if malloc fails*/
void	remove_env_key(char ***envp, char *key)
{
	int		i;
	int		j;
	char	**new_env;
	int		len;

	i = 0;
	j = 0;
	len = env_size(*envp);
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return ;
	while ((*envp)[i])
	{
		if (!is_matching_key((*envp)[i], key))
			new_env[j++] = ft_strdup((*envp)[i]);
		i++;
	}
	new_env[j] = NULL;
	shell_free_split(*envp);
	*envp = new_env;
}


int	ft_unset(char **tokens, char ***envp)
{
	int	i;

	i = 1;
	while (tokens[i])
	{
		remove_env_key(envp, tokens[i]);
		i++;
	}
	return (0);
}
