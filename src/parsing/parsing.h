/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:26:27 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 17:50:12 by kzarins          ###   ########.fr       */
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
char	*ft_strjoin3_no_nullcheck(char const *s1, char const *s2, \
			char const *s3);
int		is_space_or_tab(char input);
void	print_fundamental_error(int ret_val);

//token_splitter.c
int		extract_quotes(t_main *shell, t_twopointer *temp, int *in_quotes);
int		extract_unquoted(t_main *shell, t_twopointer *temp, int *in_quotes);

//token_add.c
void	initialize_token(t_token *token);
int		add_token_at_end(t_main *shell, char *str, int quote_type, bool comp);
int		dup_empty_str_token(t_main *shell, t_token *current_token, \
			t_token *token_to_add);
int		add_token_before(t_main *shell, t_token *token, t_token *new);

//token_del.c
int		free_all_tokens(t_main *shell);
int		free_one_token(t_token *token);
int		free_all_metachar(t_token *token);
int		free_whole_shell(t_main *shell);

//quote_seperation.c
int		extract_quotes(t_main *shell, t_twopointer *temp, int *in_quotes);

//between_token_op.c
t_type	get_meta_type(char *token);
int		add_meta_to_token(t_main *shell, t_token *main_token, \
			t_type meta_type, t_token *pseudo_t);
int		remove_token_from_chain(t_token *token);

//expand_str.c
int		expand_string(t_main *shell, char **str);

//here_request.c
int		ask_for_heredock_inputs(t_main *shell);
int		expand_heredoc(t_main *shell, t_heredoc *heredoc);
int		expand_all_heredocs(t_main	*shell);

//segment_operations.c
int		expand_compound_tokens(t_main *shell);
int		is_heredoc_token(t_token *token);

//tokenizer.c
int		is_space_or_tab(char input);
int		extract_redirections(t_main *shell, t_token **current_t, \
			t_token *temp, t_token **first_cmd);

//meta_extraction.c
int		extract_meta_smaller(t_main *shell, t_twopointer *temp);
int		extract_meta_larger(t_main *shell, t_twopointer *temp);
int		extract_meta_token(t_main *shell, t_twopointer *temp);

//add_heredoc.c
int		add_heredoc(t_main *shell, t_token *here_delimitor);
int		add_heredoc_in_linked_list(t_main *shell, t_heredoc *heredoc);
int		is_heredoc_token(t_token *token);

//redirection_assigmment.c
int		assign_redirections_to_token(t_main *shell, t_token **current_t);
int		assign_all_redirections(t_main *shell);

//token_chain_op.c
int		add_result_to_chain(t_token **chain, char *result);
int		replace_token_with_chain(t_token *token, t_token *chain);
int		free_chain(t_token *token_chain);

//segment_extraction.c
int		extract_segment(t_main *shell, t_twopointer *temp);
int		extract_unquoted_segment(t_main *shell, t_twopointer *temp, \
			int *return_val);
int		extract_quote_segment(t_main *shell, t_twopointer *temp, \
			int *in_quotes);

//compound_segments_in_toc.c
int		combine_in_one_token_meta(t_token *token, t_main *temp_shell);
int		add_one_char(char **input, char to_add);
int		combine_in_one_token_regular(t_token *token, t_main *temp_shell);

/*FOR tests!!!*/
void	print_all_tokens(t_main *shell);

#endif