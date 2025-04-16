/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:13:42 by kzarins           #+#    #+#             */
/*   Updated: 2025/04/16 22:43:10 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H
# include <stdio.h>
# include "minishell.h"

int	parsing_test(void);
int	assign_redirections_to_token(t_main *shell, t_token *start_of_cmd);
int	assign_all_redirections(t_main	*shell);
char *get_type(t_type type);

#endif