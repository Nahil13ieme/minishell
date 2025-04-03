/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:53:37 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/03 14:54:21 by nbenhami         ###   ########.fr       */
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
	if (built_in_check(cmd[0], cmd, envp) == 0)
		return (ret);
	path = find_path(cmd[0], envp);
	if (!path)
	{
		printf("%s: command not found\n", cmd[0]);
		return (127);
	}
	if (child == 1)
	{
		if (execve(path, cmd, envp) == -1)
			return (free(path), EXIT_FAILURE);
	}
	else
		ret = execute_child(path, cmd, envp);
	free(path);
	return (ret / 256);
}

int	built_in_check(char *str, char **args, char **envp)
{
	if (ft_strncmp(str, "echo",4) == 0 && ft_strlen(str) == 4)
		return(ft_echo(args), 0);
	else if (ft_strncmp(str, "cd", 2) == 0 && ft_strlen(str) == 2)
		return(ft_cd(args[1]), 0);
	else if (ft_strncmp(str, "pwd",3) == 0 && ft_strlen(str) == 3)
		return(ft_pwd(), 0);
	else if (ft_strncmp(str, "export",6) == 0 && ft_strlen(str) == 6)
		return(ft_export(args[1], envp), 0);
	else if (ft_strncmp(str, "unset",5) == 0 && ft_strlen(str) == 5)
		return(ft_unset(args[1]), 0);
	else if (ft_strncmp(str, "env",3) == 0 && ft_strlen(str) == 3)
		return(ft_env(envp), 0);
	else if (ft_strncmp(str, "exit",4) == 0 && ft_strlen(str) == 4)
		return(ft_exit(args[1]), 0);
	else
		return(1);
}
