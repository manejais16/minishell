/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:31:33 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/07 21:36:55 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", ft_strlen("env") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **tokens, t_main *shell)
{
	if (ft_strncmp(tokens[0], "echo", ft_strlen("echo") + 1) == 0)
		return (ft_echo(tokens));
	if (ft_strncmp(tokens[0], "pwd", ft_strlen("pwd") + 1) == 0)
		return (ft_pwd(tokens));
	if (ft_strncmp(tokens[0], "exit", ft_strlen("exit") + 1) == 0)
		return (ft_exit(tokens, shell));
	if (ft_strncmp(tokens[0], "cd", ft_strlen("cd") + 1) == 0)
		return (ft_cd(tokens));
	if (ft_strncmp(tokens[0], "env", ft_strlen("env") + 1) == 0)
		return (ft_env(tokens, shell->envp));
	if (ft_strncmp(tokens[0], "unset", ft_strlen("unset") + 1) == 0)
		return (ft_unset(tokens, shell));
	return (1);
}
