/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:51:42 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/04 16:48:00 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Commande built-in pour ecrire dans la sortie.
 * @param args Parametre a ecrire en char **
 */
void	ft_echo(char **args)
{
	int	i;
	int	newline;
	int	j;

	i = 1;
	j = 0;
	newline = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	i = ft_while_echo(args, i, j);
	if (newline)
		printf("\n");
}

/**
 * @brief Commande built-in pour changer de repertoire.
 * @param path Nouveau chemin desirer. en char *
 */
int	ft_cd(char *path)
{
	char	**envi;
	int		del;
	int		i;

	i = 0;
	envi = sim_glob(NULL, 'g');
	del = 1;
	while (envi[i])
	{
		if (ft_strncmp(envi[i], "HOME=", 5) == 0)
			del = 0;
		i++;
	}
	if (!path && del == 0)
		path = getenv("HOME");
	else if (del == 1)
	{
		printf("minishell: cd: HOME not set\n");
		set_exit_code(1);
	}
	if (chdir(path) != 0)
		return (perror("cd"), 1);
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
void	ft_export(char *var, char **envi)
{
	char	*equal_pos ;
	int		i;
	char	**new_envp;

	if (!var)
	{
		print_sort_export();
		return ;
	}
	equal_pos = ft_strchr(var, '=');
	i = 0;
	if ((var[0] >= '0' && var[0] <= '9') || var[0] <= 32 || ft_strlen(var) == 0
		|| ft_strchr(var, '.') != 0)
	{
		printf("minishell: export: `%c': not a valid identifier\n", var[0]);
		set_exit_code(1);
		return ;
	}
	i = ft_if_export(envi, i, var, equal_pos);
	if (i != 0)
	{
		new_envp = ft_tab_realloc(envi, 1);
		new_envp[i] = ft_strdup(var);
		new_envp[i + 1] = NULL;
		sim_glob(new_envp, 's');
		set_export();
	}
}

/**
 * @brief Commande built-in pour sortir une variable de ENV.
 * @param var Variable a unset.
 * @param envp Variable environement
 */
void	ft_unset(char *var)
{
	int		i;
	size_t	len;
	char	**envp;
	int		j;

	envp = sim_glob(NULL, 'g');
	if (!var || !envp)
		return ;
	len = ft_strlen(var);
	i = 0;
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
