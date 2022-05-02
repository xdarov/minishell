/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 21:28:03 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/15 16:29:34 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*buf_s1;
	unsigned char	*buf_s2;

	if (!s1)
		return (*(char *)s2);
	if (n == 0)
		return (0);
	i = 0;
	buf_s1 = (unsigned char *)s1;
	buf_s2 = (unsigned char *)s2;
	while (--n && buf_s1[i] == buf_s2[i])
		i++;
	return ((int)(buf_s1[i] - buf_s2[i]));
}
