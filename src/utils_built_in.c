/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:49:35 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/14 18:50:43 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_while_echo(char **args, int i, int j)
{
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			write(1, &args[i][j], 1);
			j++;
		}
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	return (i);
}

void	export_pwd(char *buf)
{
	char	*cwd;
	char	*oldpwd;
	char	*env_pwd;
	char	*pwd_entry;

	(void)buf;
	env_pwd = return_env("PWD");
	if (env_pwd)
		oldpwd = ft_strjoin("OLDPWD=", env_pwd);
	else
		oldpwd = ft_strjoin("OLDPWD=", "");
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(oldpwd));
	pwd_entry = ft_strjoin("PWD=", cwd);
	ft_unset("OLDPWD", 0);
	ft_export(oldpwd, 0);
	ft_export(pwd_entry, 0);
	free(env_pwd);
	free(oldpwd);
	free(pwd_entry);
	free(cwd);
}

int	search_c(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (i);
		i++;
	}
	return (0);
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
	int	i;

	i = 1;
	if (ft_strcmp(tree->cmd[0], "echo") == 0)
		ft_echo(tree);
	else if (ft_strcmp(tree->cmd[0], "cd") == 0)
		tree->status = ft_cd(tree->cmd);
	else if (ft_strcmp(tree->cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(tree->cmd[0], "export") == 0)
		tree->status = ft_export_2(tree->cmd);
	else if (ft_strcmp(tree->cmd[0], "unset") == 0)
	{
		while (tree->cmd[i])
		{
			ft_unset(tree->cmd[i], 0);
			i++;
		}
	}
	else if (ft_strcmp(tree->cmd[0], "env") == 0)
		ft_env(sim_glob(NULL, 'g'));
	else if (ft_strcmp(tree->cmd[0], "exit") == 0)
		ft_exit(tree);
}
