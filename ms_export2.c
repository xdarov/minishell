/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:11:13 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/29 17:55:51 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_value(char **all, char *str)
{
	int	i;

	i = -1;
	while (all[++i])
		if (all[i] == str)
			return (1);
	return (0);
}

t_list	*find_var_alph(t_list *buf, char **all)
{
	t_list	*res;
	char	*str;

	res = buf;
	while (buf)
	{
		if (check_value(all, (char *)res->content))
			res = buf;
		str = ft_strdup(buf->content);
		if (ft_memchr(str, '=', ft_strlen(str)))
			*(char *)ft_memchr(str, '=', ft_strlen(str)) = '\0';
		if (ft_strncmp(str, (char *)res->content, \
		1000) < 0 && !check_value(all, (char *)buf->content))
			res = buf;
		buf = buf->next;
		free(str);
	}
	return (res);
}

void	print_var(char *var, int fd)
{
	char	*name_var;
	char	*val_var;

	name_var = ft_strdup(var);
	val_var = NULL;
	if (ft_memchr(name_var, '=', ft_strlen(var)))
	{
		val_var = ft_memchr(name_var, '=', ft_strlen(var)) + 1;
		*(char *)ft_memchr(name_var, '=', ft_strlen(var)) = '\0';
	}
	ft_putstr_fd("declare -x ", fd);
	if (val_var && *val_var)
	{
		ft_putstr_fd(name_var, fd);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(val_var, fd);
		ft_putendl_fd("\"", fd);
	}
	else
		ft_putendl_fd(name_var, fd);
	free(name_var);
}

void	print_sort(t_ms *ms, int fd)
{
	t_list	*buf;
	char	*all[1000];
	int		i;

	i = -1;
	while (++i < 1000)
		all[i] = NULL;
	i = -1;
	while (1)
	{
		buf = find_var_alph(ms->var, all);
		if (check_value(all, (char *)buf->content))
			break ;
		if (buf->vision >= 1)
			print_var(buf->content, fd);
		all[++i] = (char *)buf->content;
	}
}
