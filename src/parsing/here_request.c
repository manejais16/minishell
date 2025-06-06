/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_request.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:17:21 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/26 14:53:23 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	collect_heredoc_lines(t_heredoc *iter, char **input)
{
	char	*temp;

	if (!iter->heredoc_input)
		iter->heredoc_input = ft_strdup("");
	if (!iter->heredoc_input)
		return (free(*input), -1);
	temp = ft_strjoin3_no_nullcheck(iter->heredoc_input, *input, "\n");
	if (!temp)
		return (free(*input), -1);
	free(iter->heredoc_input);
	iter->heredoc_input = temp;
	free(*input);
	*input = readline("> ");
	if (!*input)
		return (-1);
	return (0);
}

int	expand_heredoc(t_main *shell, t_heredoc *heredoc)
{
	if (!heredoc || !heredoc->heredoc_input)
		return (-1);
	if (!heredoc->delimiter_quoted)
		if (expand_string(shell, &heredoc->heredoc_input) == -1)
			return (-1);
	return (0);
}

int	collect_empty_heredoc(t_heredoc *heredoc)
{
	heredoc->heredoc_input = ft_strdup("");
	if (!heredoc->heredoc_input)
		return (-1);
	return (0);
}

int	ask_for_heredock_inputs(t_main *shell)
{
	t_heredoc	*iter;
	char		*input;

	iter = shell->p_here;
	while (iter)
	{
		input = readline("> ");
		if (!input)
			return (-1);
		if (ft_strcmp(input, iter->delimiter) == 0)
		{
			if (collect_empty_heredoc(iter) == -1)
				return (free(input), -1);
			iter = iter->next;
			continue ;
		}
		while (ft_strcmp(input, iter->delimiter) != 0)
			if (collect_heredoc_lines(iter, &input) == -1)
				return (-1);
		free(input);
		iter = iter->next;
	}
	return (0);
}

int	expand_all_heredocs(t_main *shell)
{
	t_heredoc	*iter;

	if (!shell || !shell->p_here)
		return (0);
	iter = shell->p_here;
	while (iter)
	{
		if (!iter->delimiter_quoted && iter->heredoc_input)
		{
			if (expand_heredoc(shell, iter) == -1)
				return (-1);
		}
		iter = iter->next;
	}
	return (0);
}
