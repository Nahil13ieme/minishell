/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:53:37 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/27 13:48:05 by nbenhami         ###   ########.fr       */
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

static char	*find_path(char *cmd, char **envp)
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

static void	path_not_found(char **cmd)
{
	printf("%s: command not found\n", cmd[0]);
}

int	execute_path(char **cmd, char **envp)
{
	char	*path;
	pid_t	pid1;
	int		ret;

	ret = 0;
	if (built_in_check(cmd[0], cmd, envp) == 0)
		return (ret);
	path = find_path(cmd[0], envp);
	if (!path)
		path_not_found(cmd);
	pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
	{
		if (execve(path, cmd, envp) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pid1 > 0)
		waitpid(pid1, &ret, 0);
	else if (pid1 < 0)
		exit(EXIT_FAILURE);	
	free(path);
	return (ret / 256);
}

int	built_in_check(char *str, char **args, char **envp)
{
	if (ft_strncmp(str, "echo",4) == 0)
		return(ft_echo(args), 0);
	else if (ft_strncmp(str, "cd",2) == 0)
		return(ft_cd(args[1]), 0);
	else if (ft_strncmp(str, "pwd",3) == 0)
		return(ft_pwd(), 0);
	else if (ft_strncmp(str, "export",6) == 0)
		return(ft_export(args[1], envp), 0);
	else if (ft_strncmp(str, "unset",5) == 0)
		return(ft_unset(args[1], envp), 0);
	else if (ft_strncmp(str, "env",3) == 0)
		return(ft_env(envp), 0);
	else if (ft_strncmp(str, "exit",4) == 0)
		return(ft_exit(args[1]), 0);
	else
		return(1);
}
