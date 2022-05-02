/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_getcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarr <sdarr@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:29:56 by sdarr             #+#    #+#             */
/*   Updated: 2022/04/29 09:38:29 by sdarr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*ft_search_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*res;

	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		res = ft_strjoin(tmp, cmd);
		if (!res)
			return (NULL);
		free(tmp);
		if (access(res, F_OK) == 0)
		{	
			ft_free(paths);
			return (res);
		}
		else
			free(res);
	}
	return (NULL);
}

char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*res;
	char	**paths;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == NULL)
	{
		i++;
		if (env[i] == NULL)
			return (cmd);
	}
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (cmd);
	res = ft_search_path(paths, cmd);
	if (!res)
	{
		ft_free(paths);
		return (cmd);
	}
	return (res);
}

void	ft_find_path(char **cmd, char **env)
{
	char	*path;

	if (!cmd)
	{
		perror("pipex");
		exit(1);
	}
	path = ft_get_path(cmd[0], env);
	if (execve(path, cmd, env) == -1)
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("command not found\n", 2);
		free(path);
		exit(127);
	}
	exit(1);
}
