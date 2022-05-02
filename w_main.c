/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:30:11 by sdarr             #+#    #+#             */
/*   Updated: 2022/04/29 17:34:19 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_builtin(t_ms *ms, t_cmd *cmdd, int *p)
{
	if (cmdd->fd[STDIN_FILENO] != STDIN_FILENO)
		close(cmdd->fd[STDIN_FILENO]);
	if (cmdd->next)
	{
		if (cmdd->fd[STDOUT_FILENO] == STDOUT_FILENO)
			cmdd->fd[STDOUT_FILENO] = p[PIPE_IN];
		cmdd->next->fd[STDIN_FILENO] = p[PIPE_OUT];
	}
	if (cmdd && !ft_memcmp(cmdd->cmd[0], "echo", 5))
		c_echo(ms, cmdd);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "env", 4))
		c_env(ms, cmdd);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "pwd", 4))
		c_pwd(cmdd);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "unset", 6))
		c_unset(ms, cmdd);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "cd", 3))
		c_cd(ms, cmdd);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "export", 7))
		c_export(ms, cmdd);
	else if (cmdd && !ft_memcmp(cmdd->cmd[0], "exit", 5))
		c_exit(ms, cmdd);
}

void	child_main(t_ms *ms, t_cmd *cmdd, int *p, int *i)
{
	char				**envv;

	if (cmdd->next)
		cmdd->next->fd[STDIN_FILENO] = p[PIPE_OUT];
	if (cmdd->next && cmdd->fd[STDOUT_FILENO] == STDOUT_FILENO)
		cmdd->fd[STDOUT_FILENO] = p[PIPE_IN];
	signal(SIGINT, child_handler);
	signal(SIGQUIT, child_handler);
	ms->pids[*i] = fork();
	if (ms->pids[*i] == 0)
	{
		signal(SIGTSTP, SIG_DFL);
		envv = get_myenv(ms);
		apply_redirect(cmdd, p);
		ft_find_path(cmdd->cmd, envv);
	}
	++(*i);
}

void	loop_cmd(t_ms *ms, t_cmd *cmdd, int *i, int *p)
{
	while (cmdd)
	{
		if (!cmdd->cmd[0])
		{
			cmdd = cmdd->next;
			continue ;
		}
		pipe(p);
		if (is_builtin(cmdd))
			run_builtin(ms, cmdd, p);
		else
			child_main(ms, cmdd, p, i);
		close(p[PIPE_IN]);
		if (cmdd->fd[STDOUT_FILENO] != STDOUT_FILENO)
			close(cmdd->fd[STDOUT_FILENO]);
		if (cmdd->fd[STDIN_FILENO] != STDIN_FILENO)
			close(cmdd->fd[STDIN_FILENO]);
		cmdd = cmdd->next;
	}
}

int	exec_proc(t_ms *ms)
{
	t_cmd	*cmdd;
	int		i;
	int		j;
	int		status;
	int		p[2];

	create_pids(ms);
	i = 0;
	cmdd = ms->cmd;
	loop_cmd(ms, cmdd, &i, p);
	close(p[PIPE_OUT]);
	close(p[PIPE_IN]);
	j = -1;
	while (++j < i)
	{
		waitpid(ms->pids[j], &status, 0);
		ms->error = WEXITSTATUS(status);
	}
	return (status);
}
