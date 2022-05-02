/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:08:28 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/28 17:08:29 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(int error, t_ms *ms, char *arg)
{
	if (error == 1)
	{
		ft_putendl_fd("shell: exit: too many arguments", 2);
		ms->error = 1;
	}
	if (error == 2)
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
		ms->error = 255;
	}
}

int	str_isdigit(char *arg)
{
	if (arg && (*arg == '+' || *arg == '-'))
		++arg;
	while (arg && *arg)
	{
		if (!ft_isdigit(*arg))
			return (1);
		++arg;
	}
	return (0);
}

void	c_exit(t_ms *ms, t_cmd *cmd)
{
	int		len;
	long	e;

	len = 0;
	while (cmd->cmd[len])
		++len;
	if (str_isdigit(cmd->cmd[1]))
		exit_error(2, ms, cmd->cmd[1]);
	else if (len > 2)
		exit_error(1, ms, cmd->cmd[1]);
	if (!ms->error)
		e = ft_atoi(cmd->cmd[1]);
	else if (ft_atoi(cmd->cmd[1]) < 0)
		e = 255;
	else
		e = ft_atoi(cmd->cmd[1]);
	if (count_cmd(ms) == 1 && (!ms->error || ms->error == 255))
	{
		ft_putendl_fd("exit", 1);
		exit(e);
	}
}
