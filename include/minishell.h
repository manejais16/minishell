/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:49:49 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/02 10:13:08 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
#include <sys/types.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_shell
{
	char	**envp;

}	t_shell;



void	setup_signals(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	init_terminal_settings(void);
char	**tokenize_input(char *input);
void	free_tokens(char **tokens);
void	execute_command(char **tokens, t_shell *shell);
char	*try_paths(char **paths, char *command);
char	*resolve_path(char *command, char **envp);
void	shell_free_split(char **arr);
char	**get_paths_from_env(char **envp);
void	exec_child(char *path, char **tokens, char **envp);
int		is_builtin(char *cmd);
int 	execute_builtin(char **tokens, t_shell *shell);
int		ft_echo(char **tokens);
int		ft_pwd(char **tokens);
int		is_numeric(char *str);
int		ft_exit(char **tokens);
int		ft_cd(char **tokens);
char	**copy_envp(char **envp);
int		ft_env(char **tokens, char **envp);
int		env_size(char **envp);
void	remove_env_key(char ***envp, char *key);
int		ft_unset(char **tokens, char ***envp);
int		is_matching_key(char *env_var, char *key);



extern int g_exit_status;




#endif
