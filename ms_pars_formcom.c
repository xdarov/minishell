/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pars_formcom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:17:50 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/29 16:56:06 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*string_assembler(t_list *com, char *line)
{
	char	*r_line;
	t_list	*temp;

	temp = com;
	r_line = ft_calloc(1, 1);
	while (temp)
	{
		r_line = ft_strjoin_free(r_line, temp->content, 2);
		if (temp->vision == 0)
			r_line = ft_strjoin_free(r_line, " ", 2);
		temp = temp->next;
	}
	free(line);
	return (r_line);
}

void	retrieve_value(t_list *temp, t_list *var)
{
	char	*ns;
	char	**s;
	int		i;

	s = ft_split(temp->content, '$');
	i = -1;
	ns = NULL;
	if (*(char *)temp->content == '$')
		ns = ft_strdup(variable_value(find_variable(var, s[++i])));
	else
		ns = ft_strdup(s[++i]);
	while (s[i] && s[++i])
		ns = ft_strjoin_free(ns, variable_value(find_variable(var, s[i])), 2);
	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
	free(temp->content);
	temp->content = ns;
}

void	format2(t_list *temp, int i)
{
	char	*ns;
	char	*s;

	s = temp->content;
	if (s[ft_strlen(s) - 1] == i)
		s[ft_strlen(s) - 1] = '\0';
	if (*s)
		++s;
	if (!ft_memcmp(s, ">", 2) || !ft_memcmp(s, "<", 2) || !ft_memcmp(s, "|", 2) \
	|| !ft_memcmp(s, "<<", 3) || !ft_memcmp(s, ">>", 3))
	{
		temp->vision += 10;
		ns = ft_strjoin(" ", s);
	}
	else
		ns = ft_strdup(s);
	free(temp->content);
	temp->content = ns;
}

void	format1(t_list *temp, t_ms *ms, char *ns)
{
	t_list	*buf;
	char	*s;
	int		i;

	s = temp->content;
	buf = NULL;
	while (*s)
	{
		i = -1;
		while (*s && *s != '$')
			ns[++i] = *s++;
		if (i == -1)
			while (*s && (*s == '$' || i == 0 || ft_isalnum(*s)))
				ns[++i] = *s++;
		ns[++i] = '\0';
		ft_lstadd_back(&buf, ft_lstnew(ft_strdup(ns)));
		retrieve_value(ft_lstlast(buf), ms->var);
	}
	temp->content = string_assembler(buf, temp->content);
	free_tlist(buf);
}

void	format_command(t_ms *ms, char *buf)
{
	t_list	*temp;
	char	*str;

	temp = ms->com;
	while (temp)
	{
		str = temp->content;
		if (str && *str == 34)
		{
			format2(temp, 34);
			format1(temp, ms, buf);
		}
		else if (str && *str == 39)
			format2(temp, 39);
		else if (str && *str)
			format1(temp, ms, buf);
		temp = temp->next;
	}
}
