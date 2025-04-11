/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:50:53 by blohrer           #+#    #+#             */
/*   Updated: 2025/02/10 15:08:54 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

char	**parse_command(char *cmd, char **envp);
void	open_files(const char *infile, const char *outfile, int *fd_in,
			int *fd_out);
void	ft_free_array(char **arr);
void	create_pipe(int pipe_fds[2]);
void	execute_child(char **cmd_args, int fd_in, int fd_out, int close_fd);
void	execute_pipe(char **cmd1_args, char **cmd2_args, int fd_in, int fd_out);
char	**get_path_from_envp(char **envp);
char	*find_command_path(char *cmd, char **envp);

#endif
