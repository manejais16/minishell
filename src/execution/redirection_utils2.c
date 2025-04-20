/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 08:45:25 by blohrer           #+#    #+#             */
/*   Updated: 2025/04/20 08:45:51 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_redirections(t_token *token)
{
	t_metachar	*meta;

	if (!token || !token->meta)
		return ;
	meta = token->meta;
	while (meta)
	{
		if (meta->fd > 0)
		{
			close(meta->fd);
			meta->fd = -1;
		}
		meta = meta->next;
	}
}
