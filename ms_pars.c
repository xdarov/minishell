/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:33:57 by pcorina           #+#    #+#             */
/*   Updated: 2022/09/11 14:02:37 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_command(t_ms *ms)
{
	t_list	*temp;
	t_cmd	*tcmd;
	char	**cmd;
	int		i;

	temp = ms->com;
	tcmd = NULL;
	while (temp)
	{
		cmd = (char **)malloc(sizeof(char *) * num_of_com(temp));
		i = -1;
		while (temp && ft_memcmp(temp->content, "|", 2))
		{
			cmd[++i] = temp->content;
			temp = temp->next;
		}
		cmd[++i] = NULL;
		cmd_add_back(&tcmd, new_cmd(cmd));
		if (temp)
			temp = temp->next;
	}
	ms->cmd = tcmd;
}

int	validation(t_ms *ms)
{
	t_list	*temp;
	char	*c;
	char	*c_next;

	temp = ms->com;
	while (temp)
	{
		if (temp->next)
			c_next = temp->next->content;
		else
			c_next = NULL;
		c = temp->content;
		if (*c == '|' && (c[1] != '\0' || temp == ms->com || !c_next))
			return (pars_error(2, ms, NULL));
		else if (check_metasim(c) && !c_next)
			return (pars_error(1, ms, NULL));
		else if (check_metasim(c) && !ft_memcmp(c_next, "|", 2))
			return (pars_error(2, ms, NULL));
		temp = temp->next;
	}
	return (0);
}

int	pars(t_ms *ms)
{
	char	*buf;

	buf = (char *)malloc(ft_strlen(ms->line) + 1);
	fill_commands(ms, buf);
	format_command(ms, buf);
	ms->error = validation(ms);
	free(buf);
	split_command(ms);
	if (!ms->error || ms->error == 1)
		check_redirect(ms);
	return (ms->error);
}
