/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:08:16 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/28 17:08:17 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	c_env(t_ms *ms, t_cmd *cmd)
{
	t_list	*buf;

	buf = ms->var;
	while (buf)
	{
		if (buf->vision == 1)
		{
			ft_putstr_fd((char *)buf->content, cmd->fd[1]);
			ft_putstr_fd("\n", cmd->fd[1]);
		}
		buf = buf->next;
	}
}
