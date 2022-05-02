/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pars_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:32:01 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/29 19:17:50 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_error(int error, t_ms *ms, char *file)
{
	if (error == 1)
		ft_putstr_fd("shell: syntax error near unexpected token `newline'\n", 2);
	else if (error == 2)
		ft_putstr_fd("shell: syntax error near unexpected token `|'\n", 2);
	if (error == 1 || error == 2)
		return (258);
	if (error == 3)
	{
		ft_putstr_fd("shell: ", 2);
		perror(file);
		ms->error = 1;
	}
	return (1);
}

void	redirect_right(t_cmd *temp, int i, t_ms *ms)
{
	int		fd;
	char	**cmd;

	cmd = temp->cmd;
	if (cmd[i][1] == '>')
		fd = open(cmd[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(cmd[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		pars_error(3, ms, cmd[i + 1]);
		temp->cmd[0] = NULL;
	}
	else
	{
		if (temp->fd[1] != 1)
			close(temp->fd[1]);
		temp->fd[1] = fd;
	}
	while (cmd[++i])
		cmd[i - 1] = cmd[i + 1];
}

void	heredoc(t_cmd *temp, int i)
{
	char	**cmd;
	char	*hd;
	char	*rl;
	int		p[2];

	hd = NULL;
	cmd = temp->cmd;
	rl_replace_line("", 0);
	rl = readline("> ");
	while (rl && (!ft_strnstr(cmd[i + 1], rl, ft_strlen(rl)) || !*rl))
	{
		hd = ft_strjoin_free(hd, rl, 6);
		hd = ft_strjoin_free(hd, "\n", 2);
		rl = readline("> ");
	}
	free(rl);
	pipe(p);
	ft_putstr_fd(hd, p[PIPE_IN]);
	free(hd);
	close(p[PIPE_IN]);
	temp->fd[0] = p[0];
}

void	redirect_left(t_cmd *temp, int i, t_ms *ms)
{
	int		fd;
	char	**cmd;

	cmd = temp->cmd;
	if (cmd[i][1] == '<')
		heredoc(temp, i);
	else
	{
		fd = open(cmd[i + 1], O_RDONLY, 0644);
		if (fd == -1)
		{
			if (temp->fd[0] != 0)
				close(temp->fd[0]);
			pars_error(3, ms, cmd[i + 1]);
			temp ->cmd[0] = NULL;
		}
		else
		{
			if (temp->fd[0] != 0)
				close(temp->fd[0]);
			temp->fd[0] = fd;
		}
	}
	while (cmd[++i])
		cmd[i - 1] = cmd[i + 1];
}

void	check_redirect(t_ms *ms)
{
	t_cmd	*temp;
	int		i;

	temp = ms->cmd;
	while (temp)
	{
		i = -1;
		while (temp->cmd[++i])
		{
			if (!ft_memcmp(temp->cmd[i], ">", 2) \
			|| !ft_memcmp(temp->cmd[i], ">>", 3))
				redirect_right(temp, i--, ms);
			else if (!ft_memcmp(temp->cmd[i], "<", 2) \
			|| !ft_memcmp(temp->cmd[i], "<<", 3))
				redirect_left(temp, i--, ms);
		}
		temp = temp->next;
	}
}
