/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:26:27 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/23 17:58:43 by kzarins          ###   ########.fr       */
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
int		extract_unquoted(t_main *shell, t_twopointer *temp, int *in_quotes);

//token_add.c
void	initialize_token(t_token *token);
int		add_token_at_end(t_main *shell, char *str, int quote_type, bool comp);
int		dup_empty_str_token(t_main *shell, t_token *current_token,\
			t_token *token_to_add);
int 	add_token_before(t_main *shell, t_token *token, t_token *new);

//token_del.c
int		free_all_tokens(t_main *shell);
int		free_one_token(t_token *token);
int		free_all_metachar(t_token *token);
int		free_whole_shell(t_main *shell);

//quote_seperation.c
int		extract_quotes(t_main *shell, t_twopointer *temp, int *in_quotes);

//between_token_op.c
t_type	get_meta_type(char *token);
int		add_meta_to_token(t_main *shell, t_token *main_token, t_type meta_type, t_token *pseudo_t);
int		remove_token_from_chain(t_token *token);

//expand_str.c
int	expand_string(t_main *shell, char **str);

//here_request.c
int		ask_for_heredock_inputs(t_main *shell);
int		expand_heredoc(t_main *shell, t_heredoc *heredoc);
int		expand_all_heredocs(t_main	*shell);

//segment_operations.c
int		expand_compound_tokens(t_main *shell);
int		is_heredoc_token(t_token *token);

#endif