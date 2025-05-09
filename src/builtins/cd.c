/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:47 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/26 15:16:39 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_missing_pwd_vars(t_main *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	if (!get_env_value(shell->envp, "PWD"))
		set_env_var(&shell->envp, "PWD", cwd);
	if (!get_env_value(shell->envp, "OLDPWD"))
		set_env_var(&shell->envp, "OLDPWD", cwd);
	free(cwd);
}

static char	*get_env_path(t_main *shell, char *var_name, int print_path)
{
	char	*env_value;

	env_value = get_env_value(shell->envp, var_name);
	if (!env_value)
		ft_printf("minishell: cd: %s not set\n", var_name);
	else if (print_path)
		ft_printf("%s\n", env_value);
	if (env_value)
		return (ft_strdup(env_value));
	else
		return (0);
}

static char	*get_cd_target(char **tokens, t_main *shell)
{
	char	*target;

	init_missing_pwd_vars(shell);
	if (!tokens[1])
		return (get_env_path(shell, "HOME", 0));
	if (ft_strcmp(tokens[1], "-") == 0)
		return (get_env_path(shell, "OLDPWD", 1));
	target = expand_tilde_in_path(tokens[1], shell);
	return (target);
}

static int	handle_cd_error(t_main *shell, char *target, char *old_pwd,
		char *error_msg)
{
	shell->return_value = 1;
	if (error_msg)
		perror(error_msg);
	if (target)
		free(target);
	if (old_pwd)
		free(old_pwd);
	return (1);
}

int	ft_cd(char **tokens, t_main *shell)
{
	char	*target;
	char	*old_pwd;
	int		arg_count;

	arg_count = 0;
	while (tokens[arg_count])
		arg_count++;
	target = get_cd_target(tokens, shell);
	if (target == NULL)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		return (handle_cd_error(shell, target, NULL, "cd"));
	if (chdir(target) != 0)
		return (handle_cd_error(shell, target, old_pwd, "cd"));
	if (update_pwd_vars(shell, old_pwd) != 0)
		return (handle_cd_error(shell, target, old_pwd, NULL));
	free(target);
	free(old_pwd);
	return (0);
}
