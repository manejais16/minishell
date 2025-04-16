/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:31:04 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/16 18:07:29 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(char *path, char **tokens, char **envp)
{
	execve(path, tokens, envp);
	perror("minishell");
	free(path);
	exit(127);
}

void	execute_external(char **tokens, char **envp)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = resolve_path(tokens[0], envp);
	if (!path)
	{
		ft_printf("Command not found: %s\n", tokens[0]);
		g_exit_status = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		exec_child(path, tokens, envp);
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

void execute_command(char **tokens, t_main *shell)
{
	if (!tokens || !*tokens)
		return;
	if (is_builtin(tokens[0]))
	{
		g_exit_status = execute_builtin(tokens, shell);
		return;
	}
	execute_external(tokens, shell->envp);
}

int	count_tokens_in_list(t_token *first_token)
{
	int		count;
	t_token	*current;

	count = 0;
	current = first_token;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**tokens_list_to_array(t_token *first_token)
{
	char	**tokens_array;
	int		count;
	t_token	*current;
	int		i;

	count = count_tokens_in_list(first_token);
	tokens_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tokens_array)
		return (NULL);
	i = 0;
	current = first_token;
	while (current)
	{
		tokens_array[i] = ft_strdup(current->str);
		if (!tokens_array[i])
		{
			shell_free_split(tokens_array);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	tokens_array[i] = NULL;
	return (tokens_array);
}
