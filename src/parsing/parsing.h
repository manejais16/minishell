/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:26:27 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/11 09:27:29 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include "minishell.h"

enum e_quotes
{
	SINGLE_Q = 0,
	DOUBLE_Q
};

enum e_parsing_errors
{
	UNCLOSED_QUOTES = -1,
	ILEGAL_CHAR = -2,
	MALLOC_FAIL = -3
};

typedef struct s_twopointer
{
	char	*p_slow;
	char	*p_fast;
}	t_twopointer;

//quote_and_meta_utils.c
int		is_quotes(const char input);
void	change_quote_state(int *state, const char input);
int		is_meta_char(const char input);
int		is_in_quotes(int in_quotes[2]);
char	get_current_quotes(int int_quotes[2]);

//token_counter.c
int		count_words(char const *s);

//parsing_utils.c
char	*substr_dangeros(char const *s, size_t len);
int		get_token_quote_type(int *in_quotes);

//token_splitter.c
int		extract_quotes(t_main *shell, t_twopointer *temp, int *in_quotes);
int		extract_unquoted(t_main *shell, t_twopointer *temp, int *return_val);

//token_add_and_dell.c
int		add_token_at_end(t_main *shell, char *str, int quote_type);
int		free_all_tokens(t_main *shell);

//quote_seperation.c
int		extract_quotes(t_main *shell, t_twopointer *temp, int *in_quotes);

#endif