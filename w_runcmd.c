/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_runcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarr <sdarr@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:33:45 by sdarr             #+#    #+#             */
/*   Updated: 2022/04/29 09:35:43 by sdarr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_myenv(t_ms *ms)
{
	int		l;
	int		i;
	char	**myenv;
	t_list	*temp;

	temp = ms->var;
	l = ft_lstsize(temp);
	myenv = malloc(sizeof(char *) * l + 1);
	if (!myenv)
		return (NULL);
	i = -1;
	while (temp)
	{
		if (temp->vision)
			myenv[++i] = temp->content;
		temp = temp->next;
	}
	myenv[i] = NULL;
	return (myenv);
}

void	create_pids(t_ms *ms)
{
	int	i;

	ms->c_cmd = count_cmd(ms);
	i = -1;
	ms->pids = malloc(sizeof(int) * (ms->c_cmd));
	if (!ms->pids)
		exit(1);
	while (++i < ms->c_cmd)
	{
		ms->pids[i] = 0;
	}
}

int	count_cmd(t_ms *ms)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = ms->cmd;
	while (cmd)
	{
		cmd = cmd -> next;
		i++;
	}
	return (i);
}

void	apply_redirect(t_cmd *cmdd, int *p)
{
	if (cmdd->fd[STDIN_FILENO] != STDIN_FILENO)
	{
		dup2(cmdd->fd[STDIN_FILENO], STDIN_FILENO);
		close(cmdd->fd[STDIN_FILENO]);
	}
	if (cmdd->fd[STDOUT_FILENO] != STDOUT_FILENO)
	{
		dup2(cmdd->fd[STDOUT_FILENO], STDOUT_FILENO);
		close(cmdd->fd[STDOUT_FILENO]);
	}
	close(p[PIPE_IN]);
	close(p[PIPE_OUT]);
}

int	is_builtin(t_cmd *cmdd)
{
	if (cmdd && !ft_memcmp(cmdd->cmd[0], "echo", 5))
		return (1);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "env", 4))
		return (1);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "pwd", 4))
		return (1);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "unset", 6))
		return (1);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "cd", 3))
		return (1);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "export", 7))
		return (1);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "exit", 5))
		return (1);
	return (0);
}
