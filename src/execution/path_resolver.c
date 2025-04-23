/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:35:31 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/23 15:31:36 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**get_paths_from_env(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

/*TODO: If tmp ft_strjoin fails it does not propogate
the the message that the strjoin failed.
+ if the full_path str does not get created
the free statement will try to free something 
that does not exist.*/
char	*try_paths(char **paths, char *command)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	ft_putstr_fd("bash:", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (NULL);
}

char	*resolve_path(char *command, char **envp)
{
	char	**paths;
	char	*full_path;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);	
	full_path = try_paths(paths, command);
	shell_free_split(paths);
	return (full_path);
}


