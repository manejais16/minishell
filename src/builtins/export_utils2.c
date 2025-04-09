/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:08:48 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/09 19:09:28 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_entry(char *name, char *value)
{
	char	*entry;
	int		name_len;
	int		value_len;
	int		total_len;

	name_len = ft_strlen(name);
	if (value)
	{
		value_len = ft_strlen(value);
		total_len = name_len + value_len + 2;
		entry = malloc(total_len);
		if (!entry)
			return (NULL);
		ft_strcpy(entry, name);
		ft_strcat(entry, "=");
		ft_strcat(entry, value);
	}
	else
	{
		entry = ft_strdup(name);
	}
	return (entry);
}
