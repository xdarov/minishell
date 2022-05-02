/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 21:28:50 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/13 17:33:41 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	counts_str(char *s, char c)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			result++;
		i++;
	}
	return (result);
}

int	size_str(char *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && *s)
		s++;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

static void	*error(char **text, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(text[j]);
		j++;
	}
	free(text);
	return ((void *)0);
}

char	**fill_text(char **text, char *buf, char c)
{
	int	i;
	int	k;
	int	str_len;

	i = 0;
	str_len = counts_str(buf, c);
	while (i < str_len)
	{
		k = 0;
		text[i] = (char *)malloc(sizeof(char) * (size_str(buf, c) + 1));
		if (!text[i])
			return (error(text, i));
		while (*buf == c && *buf)
			buf++;
		while (*buf != c && *buf)
		{
			text[i][k] = *buf;
			buf++;
			k++;
		}
		text[i][k] = '\0';
		i++;
	}
	return (text);
}

char	**ft_split(char const *s, char c)
{
	char	**text;
	int		str_len;
	char	*buf;

	if (!s)
		return ((void *)0);
	buf = (char *)s;
	str_len = counts_str(buf, c);
	text = (char **)malloc(sizeof(char *) * (str_len + 1));
	if (!text)
		return ((void *)0);
	fill_text(text, buf, c);
	text[str_len] = ((void *)0);
	return (text);
}
