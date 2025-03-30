/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:53:37 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/30 03:21:01 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_paths(paths), path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

static int	execute_child(char *path, char **cmd, char **envp)
{
	pid_t	pid1;
	int		ret;

	pid1 = fork();
	ret = 0;
	if (pid1 == 0)
	{
		if (execve(path, cmd, envp) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pid1 > 0)
		waitpid(pid1, &ret, 0);
	else if (pid1 < 0)
		exit(EXIT_FAILURE);
	return (ret);
}

int	execute_path(char **cmd, char **envp, int child)
{
	char	*path;
	int		ret;
	
	ret = 0;
	path = find_path(cmd[0], envp);
	if (!path)
	{
		printf("%s: command not found\n", cmd[0]);
		return(127);
	}
	if (child == 1)
	{
		if (execve(path, cmd, envp) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		ret = execute_child(path, cmd, envp);
		free(path);
		return (ret / 256);
	}
	free(path);
	return (ret / 256);
}
