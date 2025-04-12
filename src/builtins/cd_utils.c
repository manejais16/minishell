/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:37:24 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/12 11:42:17 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **envp, char *name)
{
	int	i;
	int	name_len;

	if (!envp || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (0);
}

int	update_pwd_vars(t_main *shell, char *old_pwd)
{
	char	*current_pwd;
	char	*pwd_value;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (perror("cd: getcwd"), 1);
	pwd_value = get_env_value(shell->envp, "PWD");
	if (pwd_value && !old_pwd)
		old_pwd = pwd_value;
	if (set_env_var(&shell->envp, "OLDPWD", old_pwd) != 0)
	{
		free(current_pwd);
		return (1);
	}
	if (set_env_var(&shell->envp, "PWD", current_pwd) != 0)
	{
		free(current_pwd);
		return (1);
	}
	free(shell->old_working_dir);
	shell->old_working_dir = ft_strdup(old_pwd);
	free(shell->working_dir);
	shell->working_dir = current_pwd;
	return (0);
}
