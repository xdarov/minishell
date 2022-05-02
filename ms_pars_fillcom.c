/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pars_fillcom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:14:58 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/29 16:55:58 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tlist(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst->content);
		free(lst);
		lst = temp;
	}
}

void	free_tcmd(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd->next;
		free(cmd->cmd);
		free(cmd);
		cmd = temp;
	}
}

int	check_quotes(char a)
{
	static int	ch;

	if (!a)
		return (ch = 0);
	if (ch && ch == -1)
		return (ch = 0);
	if (ch && a != ch)
		return (1);
	if (a == 39 || a == 34)
	{
		if (!ch)
			return (ch = a);
		else
			return (ch = -1);
	}
	return (0);
}

int	check_sim(char a)
{
	static int	ch;

	if (!a)
		return (ch = 0);
	if (ch && ch == a)
		return (1);
	if (ch && ch != a)
		return (ch = 0);
	if (a == '|' || a == '>' || a == '<')
	{
		ch = a;
		return (0);
	}
	if (a == ' ' || a == 34 || a == 39)
		return (0);
	return (1);
}

void	fill_commands(t_ms *ms, char *buf)
{
	int		i;
	char	*line;

	ms->com = NULL;
	line = ms->line;
	while (line && *line && *line == ' ')
		++line;
	while (line && *line)
	{
		i = -1;
		while (check_quotes(*line))
			buf[++i] = *(line++);
		if (i == -1 && check_sim(*line) + 1)
			while (check_sim(*line))
				buf[++i] = *(line++);
		buf[++i] = '\0';
		ft_lstadd_back(&ms->com, ft_lstnew(ft_strdup(buf)));
		if (*line == ' ')
			ft_lstlast(ms->com)->vision = 0;
		while (*line && *line == ' ')
			++line;
	}
}
