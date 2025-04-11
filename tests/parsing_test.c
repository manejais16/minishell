/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:12:08 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/11 09:50:00 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	parsing_test(void)
{
	char	*s = "\" There are \' Thare are \" some\" things \" ||tat << < ehy< what";
	t_main	shell;

	shell.user_input = s;
	go_through_str(&shell);
	t_token	*temp;
	temp = shell.first_token;
	while (temp)
	{
		printf(":%s:\n", temp->str);
		temp = temp->next;
	}
	free_all_tokens(&shell);
	if (shell.first_token)
		printf("\e[0;101mfree_all_tokens does not work!!\e[0m\n");
	else
		printf("\e[0;102mTokens freed sucessfully!\e[0m\n");
	// printf("%d\n", count_words(s));
	// s = ft_strdup("asd asd 0a");
	// printf("%d\n", count_words(s));
	return (0);
}
