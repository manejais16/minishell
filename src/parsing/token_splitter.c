/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_splitter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:33:12 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/08 17:33:15 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
