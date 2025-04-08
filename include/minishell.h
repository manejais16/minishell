/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:49:49 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/08 15:25:07 by kzarins          ###   ########.fr       */
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
	int				pipe_fd[2];
	bool			pipe_open[2];
	pid_t			pid;
	int				status;
}					t_heredoc;

typedef enum s_type
{
	larger,
	smaller,
	d_larger,
	d_smaller
}					t_type;

typedef struct s_metachar
{
	t_type			type;
	bool			open_close;
	int				fd;
	bool			read_write;
}					t_metachar;

typedef struct s_token
{
	char			*str;
	int				type;
	bool			quotes;
	bool			var_exists;
	struct t_token	*prev;
	struct t_token	*next;
	t_metachar		*meta;
}					t_token;

void				setup_signals(void);
void				handle_sigint(int sig);
void				handle_sigquit(int sig);
void				init_terminal(t_main *shell);
char				**tokenize_input(char *input);
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
int					ft_cd(char **tokens);
char				**copy_envp(char **envp);
int					ft_env(char **tokens, char **envp);
int					env_size(char **envp);
int					is_valid_identifier(char *name);
int					is_matching_name(char *env_var, char *name);
int					remove_env_name(char ***envp, char *name);
int					ft_unset(char **tokens, t_main *shell);
int					count_words(char const *s);

extern int					g_exit_status;

#endif
