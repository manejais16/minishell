/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:05:51 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/09 19:07:15 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env_variables(char **env_array, int size)
{
	int		i;
	int		j;
	char	*temp;
	int		swapped;

	i = 0;
	while (i < size - 1)
	{
		swapped = 0;
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(env_array[j], env_array[j + 1]) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
				swapped = 1;
			}
			j++;
		}
		if (swapped == 0)
			break ;
		i++;
	}
}

void	print_export_entry(char *env_entry)
{
	char	*equal_sign;
	char	*value;
	int		i;

	equal_sign = ft_strchr(env_entry, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		ft_printf("declare -x %s=\"", env_entry);
		value = equal_sign + 1;
		i = 0;
		while (value[i])
		{
			if (value[i] != '\"')
				ft_printf("%c", value[i]);
			i++;
		}
		ft_printf("\"\n");
		*equal_sign = '=';
	}
	else
		ft_printf("declare -x %s\n", env_entry);
}

int	print_sorted_export(char **envp)
{
	int		count;
	char	**sorted_copy;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	sorted_copy = malloc(sizeof(char *) * (count + 1));
	if (!sorted_copy)
		return (1);
	i = 0;
	while (i < count)
	{
		sorted_copy[i] = envp[i];
		i++;
	}
	sorted_copy[i] = NULL;
	sort_env_variables(sorted_copy, count);
	i = 0;
	while (sorted_copy[i])
		print_export_entry(sorted_copy[i++]);
	free(sorted_copy);
	return (0);
}

int	is_valid_identifier_export(char *name)
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

int	update_existing_var(char **env, char *name, char *new_entry)
{
	int	i;
	int	name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && (env[i][name_len] == '='
			|| env[i][name_len] == '\0'))
		{
			free(env[i]);
			env[i] = new_entry;
			return (1);
		}
		i++;
	}
	return (0);
}
