/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:12:08 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/08 15:24:43 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	parsing_test(void)
{
	char	*s = "\" There are \' Thare are \" some\' \'\" things \" |tat";
	printf("%d\n", count_words(s));
	return (0);
}
