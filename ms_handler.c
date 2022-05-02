/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:52:42 by sdarr             #+#    #+#             */
/*   Updated: 2022/04/29 17:06:55 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_handler(int sig)
{
	if (sig)
		;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	child_handler(int sig)
{
	ft_putstr_fd("\n", 1);
	signal(sig, child_handler);
}

void	signal_change(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sa.sa_handler = ms_handler;
	sigaction(SIGINT, &sa, NULL);
}
