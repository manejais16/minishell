/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:12:08 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/09 16:07:37 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	parsing_test(void)
{
	char	*s = "\" There are \' Thare are \" some\" things \" ||tat";
	t_main	shell;

	shell.user_input = s;
	go_through_str(&shell);
	while (shell.first_token)
	{
		printf(":%s:\n", shell.first_token->str);
		shell.first_token = shell.first_token->next;
	}
	// printf("%d\n", count_words(s));
	// s = ft_strdup("asd asd 0a");
	// printf("%d\n", count_words(s));
	return (0);
}
