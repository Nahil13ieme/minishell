/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:51:42 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/10 14:26:10 by tle-saut         ###   ########.fr       */
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
	char	**args;

	args = tree->cmd;
	i = 1;
	newline = 1;
	j = 0;
	while (args[i] && args[i][j] == '-')
	{
		j = 0;
		while (args[i][++j] == 'n')
		{
		}
		if (args[i][j] == '\0')
		{
			newline = 0;
			i++;
		}
	}
	j = 0;
	i = ft_while_echo(args, i, j);
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

	home = return_env("HOME");
	buff = NULL;
	if (args[1] == NULL)
	{
		if (home == NULL)
			return (free(home), ft_fprintf("Something disapear"));
		free(home);
		home = getenv("HOME");
		chdir(home);
		export_pwd(buff);
	}
	else if (chdir(args[1]) == 0 && args[2] == NULL)
	{
		export_pwd(buff);
		free(home);
	}
	else
		return (ft_fprintf("minishell: cd: too many arguments\n"), 1);
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
	{
		print_sort_export();
		return (0);
	}
	equal_pos = ft_strchr(var, '=');
	if (var[0] == '=' || ft_isdigit(var[0]))
		return (ft_fprintf("minishell: export: %s not a valid identifier\n",
				var), 1);
	i = ft_if_export(i, var, equal_pos);
	if (i != 0)
	{
		new_envp = ft_tab_realloc(envi, 1);
		new_envp[i] = ft_strdup(var);
		new_envp[i + 1] = NULL;
		sim_glob(new_envp, 's');
		set_export();
	}
	return (0);
}

/**
 * @brief Commande built-in pour sortir une variable de ENV.
 * @param var Variable a unset.
 * @param envp Variable environement
 */
void	ft_unset(char *var, int i)
{
	size_t	len;
	char	**envp;
	int		j;

	envp = sim_glob(NULL, 'g');
	if (!var || !envp)
		return ;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
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
	return ;
}
