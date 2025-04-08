/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:33:12 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/08 20:02:40 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/*
static char	*next_token(const char *str, char c, int *k)
{
	char	*word;
	int		start;
	int		end;

	while (str[*k] && str[*k] == c)
		(*k)++;
	start = *k;
	while (str[*k] && str[*k] != c)
		(*k)++;
	end = *k;
	word = ft_substr(str, start, end - start);
	if (word == NULL)
		return (NULL);
	return (word);
}

static int	fill_split(char **result, const char *str, char c, int word_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < word_count)
	{
		result[i] = next_word(str, c, &j);
		if (result[i] == NULL)
		{
			free_split(result, i);
			return (0);
		}
		i++;
	}
	result[i] = NULL;
	return (1);
}

char	*split_tokens(const char *str, char c)
{
	char	**result;
	int		word_count;

	if (str == NULL)
		return (NULL);
	word_count = count_words(str, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if (!fill_split(result, str, c, word_count))
		return (NULL);
	return (result);
}
*/
/*
static int	count_quotes(const char **s, int *in_quotes, int *count)
{
	change_quote_state(in_quotes, **s);
	(*count)++;
	(*s)++;
	while (**s && **s != get_current_quotes(in_quotes))
		(*s)++;
	if (**s)
	{
		change_quote_state(in_quotes, get_current_quotes(in_quotes));
		(*s)++;
	}
	return (0);
}
/*TODO: Still on development!!!
static int	go_through_str(t_main *shell)
{
	t_twopointer	temp;
	int				in_quotes[2];
	int				count;

	temp.p_fast = shell->user_input;
	 = p_first;
	count = 0;
	ft_memset(in_quotes, 0, sizeof(int) * 2);
	while (*p_second)
	{
		if (is_quotes(*p_second) && !is_in_quotes(in_quotes))
			count_quotes(s, in_quotes, count);
		else if (is_meta_char(**s) && **s != ' ')
		{
			(*count)++;
			(*s)++;
		}
		else if (**s != ' ' && (ft_isalnum(**s) || **s == '_'))
		{
			while (ft_isalnum(**s) || **s == '_')
				(*s)++;
			(*count)++;
		}
		else if (**s == ' ')
			(*s)++;
	}
	return (0);
}
*/