/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:12:08 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/16 17:24:54 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

char *get_type(t_type type)
{
	if (type == LARGER)
		return (">");
	else if (type == SMALLER)
		return ("<");
	else if (type == D_LARGER)
		return (">>");
	else if (type == D_SMALLER)
		return ("<<");
	return (NO_MATCH);
}

int	parsing_test(void)
{
	// char	*s = "\" There are \' Thare are \" some\" things \" ||tat << < ehy< what";
	//char	*s = "\" There are \' Thare are \" some\" things \" |tat <<'<' ehy< what";
	char *s = ">that <this >>be echo << \" change es\" | ese";
	t_main	shell;

	shell.user_input = s;
	go_through_str(&shell);
	int validity = check_for_repeating_meta(&shell);
	printf("Token validity: %d\n", validity);
	if (validity != 0)
		return (-1);
	assign_redirections_to_tokens(&shell, shell.first_token);
	t_token	*temp;
	t_metachar *meta_temp;
	temp = shell.first_token;
	while (temp)
	{
		printf(":%s:\n", temp->str);
		meta_temp = temp->meta;
		while(meta_temp)
		{
			printf("Meta type: %-8s File name: %s\n", get_type(meta_temp->type), meta_temp->file_name);
			meta_temp = meta_temp->next;
		}
		temp = temp->next;
	}
	free_all_tokens(&shell);
	if (shell.first_token)
		printf("\e[0;101mfree_all_tokens does not work!!\e[0m\n");
	else
		printf("\e[0;102mTokens freed sucessfully!\e[0m\n");
	return (0);
}
