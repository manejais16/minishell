/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:00:49 by blohrer           #+#    #+#             */
/*   Updated: 2025/02/10 09:58:56 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int		fd_in;
	int		fd_out;
	char	**cmd1_args;
	char	**cmd2_args;

	if (argc != 5)
	{
		ft_putstr_fd("Error: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	open_files(argv[1], argv[4], &fd_in, &fd_out);
	cmd1_args = parse_command(argv[2], envp);
	cmd2_args = parse_command(argv[3], envp);
	if (!cmd1_args || !cmd2_args)
	{
		ft_putstr_fd("Error parsing commands\n", 2);
		return (1);
	}
	execute_pipe(cmd1_args, cmd2_args, fd_in, fd_out);
	close(fd_in);
	close(fd_out);
	ft_free_array(cmd1_args);
	ft_free_array(cmd2_args);
	return (0);
}
