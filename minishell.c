/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:38:24 by pcorina           #+#    #+#             */
/*   Updated: 2022/05/02 20:38:43 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_var(t_ms *ms, char *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (!ft_memcmp(env, "OLDPWD=", 7))
		env = ft_strdup("OLDPWD");
	else if (!ft_memcmp(env, "SHLVL=", 6))
		env = ft_strjoin_free("SHLVL=", ft_itoa(ft_atoi(env + 6) + 1), 3);
	else if (!ft_memcmp(env, "PATH=", 5) && \
	!ft_strnstr(env, pwd, ft_strlen(env)))
	{
		env = ft_strjoin(env, ":");
		env = ft_strjoin_free(env, getcwd(NULL, 1024), 6);
	}
	else
		env = ft_strdup(env);
	ft_lstadd_back(&ms->var, ft_lstnew(env));
	free(pwd);
}

void	check_var(t_list *var)
{
	if (!find_variable(var, "PWD"))
		ft_lstadd_back(&var, ft_lstnew(ft_strdup("PWD")));
	if (!find_variable(var, "OLDPWD"))
		ft_lstadd_back(&var, ft_lstnew(ft_strdup("OLDPWD")));
	if (!find_variable(var, "SHLVL"))
		ft_lstadd_back(&var, ft_lstnew(ft_strdup("SHLVL=1")));
}

void	init_var_sig(char **env, t_ms *ms)
{
	int					i;

	signal_change();
	ms->ex = 1;
	i = 0;
	ms->home = getenv("HOME");
	ms->error = 0;
	ms->var = ft_lstnew(ft_strdup(env[i]));
	ms->pids = NULL;
	while (env[++i])
		change_var(ms, env[i]);
	check_var(ms->var);
	if (!find_variable(ms->var, "?"))
	{
		ft_lstadd_back(&ms->var, ft_lstnew(ft_strdup("?=0")));
		ft_lstlast(ms->var)->vision = -1;
	}
}

void	free_executed_com(t_ms *ms)
{
	signal_change();
	if (ms->line && *ms->line != '\0')
		change_errno(ms);
	ms->error = 0;
	free(ms->line);
	free_tlist(ms->com);
	free_tcmd(ms->cmd);
	if (ms->pids)
		free(ms->pids);
	ms->pids = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_ms				ms;

	if (argv || argc)
		;
	init_var_sig(env, &ms);
	while (ms.ex)
	{
		rl_replace_line("", 0);
		ms.line = readline("shell$ ");
		if (ms.line && *ms.line)
			add_history(ms.line);
		if (!ms.line)
		{
			ms.ex = 0;
			ft_putstr_fd("\e[1A\e[7C" "exit\n", 1);
		}
		if (!pars(&ms) || ms.error == 1)
			exec_proc(&ms);
		free_executed_com(&ms);
	}
	free_tlist(ms.var);
	return (0);
}
