/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:08:34 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/29 19:11:09 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_error(char *var)
{
	ft_putstr_fd("shell: export: ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	valid_new_var(t_ms *ms, char *var)
{
	int	i;

	if (!ft_isalpha(var[0]))
		return (ms->error = export_error(var));
	i = 0;
	while (var[++i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]))
			return (ms->error = export_error(var));
	}
	return (0);
}

void	add_var(t_ms *ms, t_cmd *cmd)
{
	char	*var_name;
	t_list	*buf;
	int		i;

	i = 0;
	while (cmd->cmd[++i])
	{
		if (valid_new_var(ms, cmd->cmd[i]))
			continue ;
		var_name = ft_strdup(cmd->cmd[i]);
		if (ft_memchr(var_name, '=', ft_strlen(var_name)))
			*(char *)ft_memchr(var_name, '=', ft_strlen(var_name)) = '\0';
		buf = find_variable(ms->var, var_name);
		free(var_name);
		if (buf)
		{
			free(buf->content);
			buf->content = ft_strdup(cmd->cmd[i]);
			buf->vision = 1;
		}
		else
			ft_lstadd_back(&ms->var, ft_lstnew(ft_strdup(cmd->cmd[i])));
	}
}

void	c_export(t_ms *ms, t_cmd *cmd)
{
	if (cmd->cmd[1])
		add_var(ms, cmd);
	else
		print_sort(ms, cmd->fd[1]);
}
