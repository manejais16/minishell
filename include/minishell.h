/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:49:49 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/19 13:05:40 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/gnl/get_next_line.h"
# include "../lib/libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_token		t_token;
typedef struct s_heredoc	t_heredoc;
typedef struct s_metachar	t_metachar;
typedef struct s_heredoc	t_heredoc;

typedef struct s_main
{
	char			**envp;
	char			*user_input;
	char			*working_dir;
	char			*old_working_dir;
	pid_t			pid;
	t_token			*first_token;
	t_token			*last_token;
	int				return_value;
	t_heredoc		*p_here;
}					t_main;

typedef struct s_heredoc
{
	char			*delimiter;
	bool			delimiter_quoted;
	bool			already_used;
	char			*heredoc_input;
	t_heredoc		*next;
}					t_heredoc;

typedef enum s_type
{
	NONE_T,
	LARGER,
	SMALLER,
	D_LARGER,
	D_SMALLER,
	PIPE
}					t_type;

typedef struct s_metachar
{
	t_type			type;
	char			*file_name;
	bool			open_close;
	int				fd;
	bool			read_write;
	t_metachar		*next;
}					t_metachar;

// enum	token_types
// {
// 	FILE_N,
// 	CMD,
// 	META
// };

typedef struct s_token
{
	char			*str;
	// int				type;
	bool			is_compound_token;
	int				quote_type;
	bool			var_exists;
	t_token			*prev;
	t_token			*next;
	t_metachar		*meta;
}					t_token;

enum	quote_type
{
	NONE = 0,
	SINGLE = 1,
	DOUBLE = 2
};

void				setup_signals(void);
void				handle_sigint(int sig);
void				handle_sigquit(int sig);
void				init_terminal(t_main *shell);
// char				**tokenize_input(char *input);
int					tokenize_input(t_main *shell);
void				free_tokens(char **tokens);
void				execute_command(char **tokens, t_main *shell);
char				*try_paths(char **paths, char *command);
char				*resolve_path(char *command, char **envp);
void				shell_free_split(char **arr);
char				**get_paths_from_env(char **envp);
void				exec_child(char *path, char **tokens, char **envp);
int					is_builtin(char *cmd);
int					execute_builtin(char **tokens, t_main *shell);
int					ft_echo(char **tokens);
int					ft_pwd(char **tokens);
int					is_numeric(char *str);
int					ft_exit(char **tokens, t_main *shell);
int					ft_cd(char **tokens, t_main *shell);
char				**copy_envp(char **envp);
int					ft_env(char **tokens, char **envp);
int					env_size(char **envp);
int					is_valid_identifier(char *name);
int					is_matching_name(char *env_var, char *name);
int					remove_env_name(char ***envp, char *name);
int					ft_unset(char **tokens, t_main *shell);
int					count_words(char const *s);
int					go_through_str(t_main *shell);
void				sort_env_variables(char **env_array, int size);
void				print_export_entry(char *env_entry);
int					print_sorted_export(char **envp);
int					is_valid_identifier_export(char *name);
int					update_existing_var(char **env, char *name, char *new_entry);
char				*create_env_entry(char *name, char *value);
int					append_env_var(char ***envp, char *new_entry);
int					set_env_var(char ***envp, char *name, char *value);
int					handle_export_with_value(char *arg, char *equal_sign, t_main *shell);
int					process_export_arg(char *arg, t_main *shell);
int					ft_export(char **tokens, t_main *shell);
int					free_all_tokens(t_main *shell);
char				*get_env_value(char **envp, char *name);
int					update_pwd_vars(t_main *shell, char *old_pwd);
int					check_for_repeating_meta(t_main *shell);
char				*expand_tilde_in_path(char *path, t_main *shell);
int					expand_variables(t_main *main);
int					expand_variables_in_token(t_main *main, t_token *token);
int					expand_variables(t_main *main);
int					perform_token_expansion(t_main *main, t_token *token, char **expanded_str);
bool				find_and_expand_vars(t_main *main, char **expanded_str);
bool				expand_var_in_string(t_main *main, char **expanded_str, size_t i);
char				*init_token_expansion(t_token *token);
char				*expand_var_at_pos(t_main *main, const char *str, size_t pos);
int					extract_string_parts(const char *str, size_t pos, size_t var_name_len, char **parts);
char				*get_expanded_value(t_main *main, const char *str, size_t *var_name_len);
char				*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char				*extract_var_name(const char *str);
size_t				get_var_name_len(const char *str);
char				*handle_exit_status(t_main *main);
char				**tokens_list_to_array(t_token *first_token);
int					count_tokens_in_list(t_token *first_token);
int					expand_tilde_in_string(t_main *main, char **str);
int					free_user_input(t_main *shell);


extern int					g_exit_status;

#endif
