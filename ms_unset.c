/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:34:26 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/28 18:34:27 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_error(char *var)
{
	ft_putstr_fd("shell: unset: ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	valid_del_var(t_ms *ms, char *var)
{
	int	i;

	if (!ft_isalpha(var[0]))
		return (ms->error = unset_error(var));
	i = 0;
	while (var[++i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]))
			return (ms->error = unset_error(var));
	}
	return (0);
}

void	c_unset(t_ms *ms, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[++i])
	{
		if (valid_del_var(ms, cmd->cmd[i]))
			continue ;
		if (find_variable(ms->var, cmd->cmd[i]))
			find_variable(ms->var, cmd->cmd[i])->vision = 0;
	}
}
