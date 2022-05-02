/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:36:52 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/29 16:54:17 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include "libft/libft.h"
# include <signal.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>

# define PIPE_IN 1
# define PIPE_OUT 0

typedef struct s_cmd
{
	char			**cmd;
	int				fd[2];
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	t_list			*var;

	t_list			*com;
	t_cmd			*cmd;

	char			*home;
	char			*line;

	int				error;
	int				ex;
	int				c_cmd;
	int				*pids;
}	t_ms;

void	c_cd(t_ms *ms, t_cmd *cmd);
void	c_unset(t_ms *ms, t_cmd *cmd);
void	c_pwd(t_cmd *cmd);
t_list	*find_variable(t_list *var, char *line);
void	c_export(t_ms *ms, t_cmd *cmd);
void	print_sort(t_ms *ms, int fd);
t_list	*find_var_alph(t_list *buf, char **all);
int		check_value(char **all, char *str);
void	c_env(t_ms *ms, t_cmd *cmd);
void	del_var(t_list **var, char *str);
void	c_echo(t_ms *ms, t_cmd *cmd);
void	add_history(char *line);
char	*variable_value(t_list *var);
void	error_com(t_ms *ms);
void	change_errno(t_ms *ms);
int		count_cmd(t_ms *ms);
void	c_exit(t_ms *ms, t_cmd *cmd);

int		pars(t_ms *ms);
void	free_tlist(t_list *lst);
void	free_tcmd(t_cmd *cmd);
int		exec_proc(t_ms *ms);
void	ms_handler(int sig);
void	child_handler(int sig);
void	change_errno(t_ms *ms);
void	c_pwd(t_cmd *cmd);
void	fill_commands(t_ms *ms, char *buf);
int		num_of_com(t_list *com);
t_cmd	*new_cmd(void *cmd);
void	cmd_add_back(t_cmd **cmd, t_cmd *new);
int		check_metasim(char *str);
void	format_command(t_ms *ms, char *buf);
int		pars_error(int error, t_ms *ms, char *file);
void	check_redirect(t_ms *ms);
void	ft_find_path(char **cmd, char **env);
char	**get_myenv(t_ms *ms);
void	create_pids(t_ms *ms);
int		count_cmd(t_ms *ms);
void	apply_redirect(t_cmd *cmdd, int *p);
int		is_builtin(t_cmd *cmdd);
void	signal_change(void);
#endif
