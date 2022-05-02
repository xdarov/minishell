/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_mini.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:07:04 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/28 17:09:54 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	c_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	ft_putendl_fd(pwd, cmd->fd[1]);
	free(pwd);
}

void	change_errno(t_ms *ms)
{
	t_list	*temp;

	temp = find_variable(ms->var, "?");
	free(temp->content);
	temp->content = ft_strjoin_free("?=", ft_itoa(ms->error), 3);
	temp->vision = -1;
}

void	del_var(t_list **var, char *str)
{
	t_list	*prev;
	t_list	*buf;
	char	*name;

	name = ft_strdup(str);
	if (ft_strchr(name, '='))
		*ft_strchr(name, '=') = '\0';
	prev = *var;
	buf = *var;
	while (buf && !ft_strnstr((char *)buf->content, name, ft_strlen(name)))
	{
		prev = buf;
		buf = buf->next;
	}
	if (buf)
	{
		if (buf != *var)
			prev->next = buf->next;
		else
			*var = buf->next;
		free(buf->content);
		free(buf);
	}
	free(name);
}
