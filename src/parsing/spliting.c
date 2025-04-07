/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 06:30:44 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/07 19:40:53 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
/*TODO: Include file to mainshell*/
#include "parsing.h"

//TODO: STILL IN DEVELOPMENT!!!
static int	count_words(char const *s)
{
	int	count;
	int in_quotes[2];

	count = 0;
	/*TODO: should replace with memset!*/
	in_quotes[0] = 0;
	in_quotes[1] = 0;
	while (*s != '\0')
	{
		if (is_quotes(*s) && !is_in_quotes(in_quotes))
		{
			change_quote_state(in_quotes, *s);
			count++;
			s++;
			while (*s && *s != get_current_quotes(in_quotes))
				s++;
			if (*s)
			{
				change_quote_state(in_quotes, get_current_quotes(in_quotes));
				s++;
			}
		}
		else
			s++;
	}
	if (in_quotes[0] || in_quotes[1])
		return (-1);
	return (count);
}
/*
static char	*next_word(const char *str, char c, int *k)
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

char	**ft_split(const char *str, char c)
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
#include <stdio.h>
int main(void)
{
	char *s = "\" There are \' Thare are \" some\' \'\" things \" ";
	printf("%d\n", count_words(s));
}
*/