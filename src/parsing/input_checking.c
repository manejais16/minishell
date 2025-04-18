/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:25:31 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/18 19:55:22 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static void	print_tokenisation_error(char *str)
{
	ft_printf("minishell: syntax error near unexpected token `%s'\n", str);
}

int	check_for_repeating_meta(t_main *shell)
{
	t_token	*temp;
	t_token	*nextp;

	temp = shell->first_token;
	while (temp)
	{
		nextp = temp->next;
		if (nextp)
		{
			if (is_meta_char(*temp->str) && temp->quote_type == NONE
				&& is_meta_char(*nextp->str) && nextp->quote_type == NONE)
			{
				print_tokenisation_error(nextp->str);
				return (-1);
			}
		}
		else if (is_meta_char(*temp->str) && temp->quote_type == NONE)
		{
			print_tokenisation_error("newline");
			return (-1);
		}
		temp = nextp;
	}
	return (0);
}
