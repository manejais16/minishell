/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:34:11 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/24 22:33:44 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_env_var(char ***envp, char *new_entry)
{
	char	**new_env;
	int		len;
	int		i;

	len = 0;
	while ((*envp)[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (1);
	i = 0;
	while ((*envp)[i])
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[i++] = new_entry;
	new_env[i] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}

int	set_env_var(char ***envp, char *name, char *value)
{
	char	*new_entry;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (1);
	if (update_existing_var(*envp, name, new_entry))
		return (0);
	if (append_env_var(envp, new_entry))
	{
		free(new_entry);
		return (1);
	}
	return (0);
}

int	handle_export_with_value(char *arg, char *equal_sign, t_main *shell)
{
	char	*name;
	char	*value;
	int		result;

	*equal_sign = '\0';
	name = arg;
	value = equal_sign + 1;
	if (is_valid_identifier_export(name))
	{
		result = set_env_var(&shell->envp, name, value);
		*equal_sign = '=';
		return (result);
	}
	else
	{
		*equal_sign = '=';
		ft_putstr_fd("bash: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
}

int	process_export_arg(char *arg, t_main *shell)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		return (handle_export_with_value(arg, equal_sign, shell));
	}
	else if (is_valid_identifier_export(arg))
	{
		return (set_env_var(&shell->envp, arg, NULL));
	}
	else
	{
		ft_printf("minishell: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
}

int	ft_export(char **tokens, t_main *shell)
{
	int	i;
	int	status;

	status = 0;
	if (!tokens[1])
		return (print_sorted_export(shell->envp));
	i = 1;
	while (tokens[i])
	{
		if (process_export_arg(tokens[i], shell))
			status = 1;
		i++;
	}
	return (status);
}
