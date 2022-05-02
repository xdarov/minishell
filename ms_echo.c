/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:08:09 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/28 17:08:10 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_print(t_ms *ms, char **cmd, int i, int fd)
{
	t_list	*temp;

	temp = ms->com;
	while (temp && temp->content != cmd[i])
		temp = temp->next;
	while (temp && cmd[i] && temp->content == cmd[i])
	{
		if (temp->vision < 10)
			ft_putstr_fd(temp->content, fd);
		else
			ft_putstr_fd(temp->content + 1, fd);
		if (temp && (!temp->vision || temp->vision == 10) && cmd[i + 1])
			ft_putstr_fd(" ", fd);
		++i;
		temp = temp->next;
	}
}

void	c_echo(t_ms *ms, t_cmd *cmd)
{
	if (cmd->cmd[1] && ft_strnstr(cmd->cmd[1], "-n", 2))
		echo_print(ms, cmd->cmd, 2, cmd->fd[1]);
	else
	{
		echo_print(ms, cmd->cmd, 1, cmd->fd[1]);
		ft_putstr_fd("\n", cmd->fd[1]);
	}
}
