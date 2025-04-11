/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:08:11 by blohrer           #+#    #+#             */
/*   Updated: 2025/02/08 09:41:00 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(const char *infile, const char *outfile, int *fd_in,
		int *fd_out)
{
	*fd_in = open(infile, O_RDONLY);
	if (*fd_in == -1)
	{
		perror("Error opening input file.");
		exit(EXIT_FAILURE);
	}
	*fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		perror("Error opening output file.");
		close(*fd_in);
		exit(EXIT_FAILURE);
	}
}

void	ft_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**get_path_from_envp(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;
	char	*tmp;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_path_from_envp(envp);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (ft_free_array(paths), cmd_path);
		free(cmd_path);
	}
	return (ft_free_array(paths), NULL);
}

char	**parse_command(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		return (ft_free_array(args), NULL);
	cmd_path = find_command_path(args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putchar_fd('\n', 2);
		return (ft_free_array(args), NULL);
	}
	free(args[0]);
	args[0] = cmd_path;
	return (args);
}
