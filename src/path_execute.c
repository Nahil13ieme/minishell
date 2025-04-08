/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:53:37 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/08 17:55:57 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;
	char 	*tmp;

	tmp = return_env("PATH");
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	free(tmp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_tab(paths), path);
		free(path);
		i++;
	}
	i = -1;
	free_tab(paths);
	return (NULL);
}

static int	execute_child(char *path, char **cmd)
{
	pid_t	pid1;
	int		ret;

	pid1 = fork();
	ret = 0;
	if (pid1 == 0)
	{
		setup_child_signals();
		if (execve(path, cmd, sim_glob(NULL, 'g')) == -1)
		{
			free_glob();
			set_root(NULL, 'f');
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid1 > 0)
		waitpid(pid1, &ret, 0);
	else if (pid1 < 0)
		exit(EXIT_FAILURE);
	return (ret / 256);
}

void	execute_path(t_btree *tree)
{
	char	*path;

	if (built_in_check(tree->cmd[0]))
	{
		exec_built_in(tree);	
		return ;
	}
	if (access(tree->cmd[0], F_OK) == 0)
		path = ft_strdup(tree->cmd[0]);
	else
		path = find_path(tree->cmd[0]);
	if (check_dir(tree) == 1)
		return (free(path));
	if (!path)
	{
		printf("%s: command not found\n", tree->cmd[0]);
		tree->status = 127;
		return ;
	}
	if (tree->child == 0)
		tree->status = execute_child(path, tree->cmd);
	else
		if (execve(path, tree->cmd, sim_glob(NULL, 'g')) == -1)
			return (free(path));
	return (free(path));
}

int	built_in_check(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

void	exec_built_in(t_btree *tree)
{
	if (ft_strcmp(tree->cmd[0], "echo") == 0)
		ft_echo(tree);
	else if (ft_strcmp(tree->cmd[0], "cd") == 0)
		tree->status = ft_cd(tree->cmd);
	else if (ft_strcmp(tree->cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(tree->cmd[0], "export") == 0)
		tree->status = ft_export(tree->cmd[1]);
	else if (ft_strcmp(tree->cmd[0], "unset") == 0)
		ft_unset(tree->cmd[1]);
	else if (ft_strcmp(tree->cmd[0], "env") == 0)
		ft_env(sim_glob(NULL, 'g'));
	else if (ft_strcmp(tree->cmd[0], "exit") == 0)
		ft_exit(tree->cmd[1]);
}
