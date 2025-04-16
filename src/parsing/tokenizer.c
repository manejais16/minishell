/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 08:58:43 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/16 17:27:53 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/*Rewrite for our builtin struct*/
char	**tokenize_input(char *input)
{
	return (ft_split(input, ' '));
}

/*TODO: Remove when all the functions are overwritten*/
void	free_tokens(char **tokens)
{
	int	i = 0;

	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

int	go_through_str(t_main *shell)
{
	t_twopointer	temp;
	int				in_quotes[2];
	int				return_val;

	temp.p_fast = shell->user_input;
	temp.p_slow = temp.p_fast;
	ft_memset(in_quotes, 0, sizeof(int) * 2);
	while (*temp.p_fast)
	{
		if (is_quotes(*temp.p_fast) && !is_in_quotes(in_quotes))
		{
			return_val = extract_quotes(shell, &temp, in_quotes);
			if (return_val < 0)
				return (return_val);
		}
		else
		{
			return_val = extract_unquoted(shell, &temp, &return_val);
			if (return_val < 0)
				return (return_val);
		}
	}
	return (0);
}

int	reassign_meta_t(t_main *shell, t_token *token, t_token **start)
{
	t_token	*temp;
	
	if (add_meta_to_token(token, get_meta_type((*start)->str), (*start)->next) == -1)
		return (-1);
	temp = (*start)->next->next;
	if (shell->first_token == *start)
		shell->first_token = temp;
	if (shell->last_token == (*start)->next)
		shell->last_token = (*start)->prev;
	remove_token_from_chain((*start)->next);
	remove_token_from_chain(*start);
	*start = temp;
	return (0);
}

/*Function that only crates files*/
/*The functino should return -1 if it fails!!!!!*/
/*TODO: Create something that just opens the files 
if there is not command between the pipes*/
int	only_create_files(t_token *token)
{
	(void)token;
	return (0);
}

/*TODO: still have to expand the token if it is $var*/
int	assign_redirections_to_tokens(t_main *shell, t_token *start_of_cmd)
{
	t_token	temp;
	t_token	*start;
	t_token	*first_cmd;

	first_cmd = NULL;
	start = start_of_cmd;
	initialize_token(&temp);
	while (*start->str != '|')
	{
		if (is_meta_char(*start->str) && *start->str != ' ')
		{
			if (reassign_meta_t(shell, &temp, &start) == -1)
				return (-1);
		}
		else
		{
			if (!first_cmd)
				first_cmd = start;
			start = start->next;
		}
		if (start == NULL)
			break ;
	}
	if (first_cmd == NULL)
		return (only_create_files(&temp), 0);
	first_cmd->meta = temp.meta;
	return (0);
}
