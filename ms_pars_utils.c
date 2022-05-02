/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:21:20 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/29 16:56:23 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void *cmd)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = cmd;
	new_cmd->fd[0] = 0;
	new_cmd->fd[1] = 1;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last;

	if (!cmd || !new)
		return ;
	last = *cmd;
	if (!last)
		*cmd = new;
	else
	{
		while (last -> next)
			last = last -> next;
		last -> next = new;
	}
}

int	num_of_com(t_list *com)
{
	t_list	*temp;
	int		count;

	temp = com;
	count = 1;
	while (temp)
	{
		if (!ft_memcmp(temp->content, "|", 2))
			break ;
		++count;
		temp = temp->next;
	}
	return (count);
}

int	check_metasim(char *str)
{
	if ((!ft_memcmp(str, ">", 2) || !ft_memcmp(str, "<", 2) || \
		!ft_memcmp(str, ">>", 3) || !ft_memcmp(str, "<<", 3)) \
		|| !ft_memcmp(str, "|", 2))
		return (1);
	return (0);
}

// void	SHOW(t_cmd *cmd, char *space)
// {
// 	t_cmd	*temp;
// 	int		i;

// 	temp = cmd;
// 	while (temp)
// 	{
// 		i = -1;
// 		printf("SHOW:%s%d-> ", space, i + 2);
// 		while (temp->cmd[++i])
// 			printf("'%s':%zu ", temp->cmd[i], ft_strlen(temp->cmd[i]));
// 		printf("| fd.in->%d fd.out->%d", cmd->fd[0], cmd->fd[1]);
// 		printf("\n");
// 		temp = temp->next;
// 	}
// }
