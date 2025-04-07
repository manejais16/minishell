/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:26:27 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/07 19:36:30 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

enum e_quotes
{
	SINGLE = 0,
	DOUBLE
};

//quote_and_meta_utils.c
int		is_quotes(const char input);
void	change_quote_state(int *state, const char input);
int		is_meta_char(const char input);
int		is_in_quotes(int in_quotes[2]);
char	get_current_quotes(int int_quotes[2]);


#endif