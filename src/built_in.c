/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:51:42 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/13 20:34:13 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Commande built-in pour ecrire dans la sortie.
 * @param args Parametre a ecrire en char **
 */
void	ft_echo(t_btree *tree)
{
	int		i;
	int		newline;
	int		j;

	i = 1;
	newline = 1;
	j = 0;
	while (tree->cmd[i] && tree->cmd[i][0] == '-' && tree->cmd[i][1])
	{
		j = 1;
		while (tree->cmd[i][j] == 'n')
			j++;
		if (tree->cmd[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	i = ft_while_echo(tree->cmd, i, 0);
	if (newline)
		printf("\n");
}

/**
 * @brief Commande built-in pour changer de repertoire.
 * @param path Nouveau chemin desirer. en char *
 */
int	ft_cd(char **args)
{
	char	*buff;
	char	*home;
	char	*pwd;

	home = return_env("HOME");
	pwd = return_env("PWD");
	buff = NULL;
	if (args[1] == NULL)
	{
		if (home == NULL)
			return (free(pwd), ft_fprintf("Something is missing, loser\n"));
		free(home);
		if (pwd)
			free(pwd);
		home = getenv("HOME");
		chdir(home);
		export_pwd(buff);
	}
	else if (pwd == NULL)
		return (free(home), free(pwd),
			ft_fprintf("Something is missing, loser\n"));
	else if (args[1][0] == '~')
		return (chdir(home), free(home), free(pwd), 0);
	else if (!args[2] && chdir(args[1]) == 0)
	{
		export_pwd(buff);
		free(home);
		free(pwd);
	}
	else if (chdir(args[1]) == -1)
	{
		free(home);
		free(pwd);
		ft_fprintf("minishell: cd: %s: No such file or directory\n", args[1]);
		return (1);
	}
	else if (args[2])
	{
		free(home);
		free(pwd);
		return (ft_fprintf("minishell: cd: too many arguments\n"), 1);
	}
	return (0);
}

/**
 * @brief Commande built-in pour afficher le chemin actuel
 */
void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
}

/**
 * @brief Commande built-in pour exporter une variable dans ENV.
 * @param var Variable a exporter.
 */
int	ft_export(char *var, int i)
{
	char	*equal_pos ;
	char	**new_envp;
	char	**envi;

	envi = sim_glob(NULL, 'g');
	if (!var)
		return (print_sort_export(), 0);
	equal_pos = ft_strchr(var, '=');
	if (var[0] == '=' || ft_isdigit(var[0]) || var[0] < 48
		|| (var[0] > 57 && var[0] <= 63))
		return (ft_fprintf("minishell: export: %s not a valid identifier\n",
				var), 1);
	i = ft_if_export(i, var, equal_pos);
	if (i > 0)
	{
		new_envp = ft_tab_realloc(envi, 1);
		new_envp[i] = ft_strdup(var);
		new_envp[i + 1] = NULL;
		sim_glob(new_envp, 's');
		set_export();
	}
	return (0);
}

int	ft_export_2(char **args)
{
	char	*equal_pos ;
	char	**new_envp;
	char	**envi;
	int		exit;
	int		i;
	int		j;
	
	i = 1;
	exit = 0;
	if (!args[i])
		return (print_sort_export(), 0);
	while (args[i])
	{
		envi = sim_glob(NULL, 'g');
		j = 0;
		equal_pos = ft_strchr(args[i], '=');
		if (args[i][0] == '=' || ft_isdigit(args[i][0]) || args[i][0] < 48
			|| (args[i][0] > 57 && args[i][0] <= 63))
			return (ft_fprintf("minishell: export: %s not a valid identifier\n",
					args[i]), 1);
		j = ft_if_export(j, args[i], equal_pos);
		if (j == -1)
			exit = 1;
		if (j > 0)
		{
			new_envp = ft_tab_realloc(envi, 1);
			new_envp[j] = ft_strdup(args[i]);
			new_envp[j + 1] = NULL;
			sim_glob(new_envp, 's');
			set_export();
		}
		i++;
	}
	if (exit == 0)
		return (0);
	return (1);
}

/**
 * @brief Commande built-in pour sortir une variable de ENV.
 * @param var Variable a unset.
 * @param envp Variable environement
 */
void	ft_unset(char *var, int i)
{
	char	**envp;
	int		j;

	envp = sim_glob(NULL, 'g');
	if (!var || !envp)
		return ;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, search_c(envp[i], '=')) == 0)
		{
			j = i;
			free(envp[i]);
			while (envp[j + 1])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j] = NULL;
		}
		else
			i++;
	}
}
