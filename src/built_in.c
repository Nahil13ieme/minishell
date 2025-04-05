/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:51:42 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/05 07:49:12 by nbenhami         ###   ########.fr       */
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
	j = 0;
	newline = 1;
	if (args[i] && args[i][j] == '-')
	{
		while (args[i][++j] == 'n');
		if (args[i][j] == '\0')
		{
			newline = 0;
			i++;
		}
	}
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
	char	**envi;
	int		del;
	int		i;

	i = 0;
	envi = sim_glob(NULL, 'g');
	del = 1;
	if (args[2])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	while (envi[i])
	{
		if (ft_strncmp(envi[i], "HOME=", 5) == 0)
			del = 0;
		i++;
	}
	if (!args[1] && del == 0)
		args[1] = getenv("HOME");
	else if (del == 1)
	{
		printf("minishell: cd: HOME not set\n");
		set_exit_code(1);
	}
	if (chdir(args[1]) != 0)
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
int	ft_export(char *var, char **envi)
{
	char	*equal_pos ;
	int		i;
	char	**new_envp;

	if (!var)
	{
		print_sort_export();
		return 0;
	}
	equal_pos = ft_strchr(var, '=');
	i = 0;
	while (var[i] && isalpha(var[i]))
		i++;
	if ((var[i] != '=' && var[i] != 0) || i == 0)
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (1);
	}
	i = ft_if_export(envi, i, var, equal_pos);
	new_envp = ft_tab_realloc(envi, 1);
	new_envp[i] = ft_strdup(var);
	new_envp[i + 1] = NULL;
	sim_glob(new_envp, 's');
	set_export();
	return (0);
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
	char	**export;

	envp = sim_glob(NULL, 'g');
	export = sim_glob(NULL, 'G');
	if (!var || !envp)
		return ;
	len = 0;
	i = 0;
	while (var[len])
		len++;
	while (envp[i])
	{
		ft_if_unset(envp, export, var, len, i);
		i++;
	}
	return ;
}
