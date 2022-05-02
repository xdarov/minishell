/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:07:53 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/28 17:07:54 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dir_init(t_ms *ms, t_cmd *cmd)
{
	char	*buf;

	if (!cmd->cmd[1])
		buf = getcwd(NULL, 1024);
	else if (!ft_memcmp(cmd->cmd[1], "--", 3) || \
	(!ft_memcmp(cmd->cmd[1], "~", 2)))
		buf = ft_strdup(ms->home);
	else if (!ft_memcmp(cmd->cmd[1], "/", 2))
		buf = ft_strdup(cmd->cmd[1]);
	else
	{
		buf = ft_strjoin_free(getcwd(NULL, 1024), "/", 2);
		buf = ft_strjoin_free(buf, cmd->cmd[1], 2);
	}
	return (buf);
}

void	error_dir(t_ms *ms)
{
	ft_putstr_fd("shell: cd: ", 0);
	perror(ms->com->next->content);
	ms->error = 1;
}

void	c_cd(t_ms *ms, t_cmd *cmd)
{
	t_list	*t_buf;
	char	*dir;

	dir = dir_init(ms, cmd);
	if (!chdir(dir))
	{
		t_buf = find_variable(ms->var, "OLDPWD");
		t_buf->vision = 1;
		free(t_buf->content);
		t_buf->content = ft_strjoin_free("OLDPWD=", getcwd(NULL, 1024), 3);
		t_buf = find_variable(ms->var, "PWD");
		t_buf->vision = 1;
		free(t_buf->content);
		t_buf->content = ft_strjoin_free("PWD=", getcwd(NULL, 1024), 3);
	}
	else
		error_dir(ms);
	free(dir);
}
