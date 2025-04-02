/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:51:42 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/02 13:24:01 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Commande built-in pour ecrire dans la sortie.
 * @param args Parametre a ecrire en char **
 */
void ft_echo(char **args)
{
	int i = 1;
	int newline = 1;
	int	j;

	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '$' && args[i][j + 1] == '?')
			{
				printf("%d", get_exit_code());
				j++;
			}
			else
			{
				printf("%c", args[i][j]);
			}
			j++;
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

/**
 * @brief Commande built-in pour changer de repertoire.
 * @param path Nouveau chemin desirer. en char *
 */
int	ft_cd(char *path)
{
	if (!path)
		path = getenv("HOME");
	if (chdir(path) != 0)
	{
		return (1);
		perror("cd");
	}
	return (0);
}

/**
 * @brief Commande built-in pour afficher le chemin actuel
 */
void	ft_pwd(void)
{
	char cwd[1024];

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
			ft_print_env(1);
			return ;
		}
	equal_pos = ft_strchr(var, '=');
	i = 0;
	if (equal_pos)
	{
		while (envi[i])
		{
			if (ft_strncmp(envi[i], var, equal_pos - var) == 0)
			{
				free(envi[i]);
				envi[i] = ft_strdup(var);
				return;
			}
			i++;
		}
	}
	else
	{
		i = 0;
		while(envi[i])
			i++;
	}
	new_envp = ft_tab_realloc(envi, 1);
	new_envp[i] = ft_strdup(var);
	new_envp[i + 1] = NULL;
	sim_glob(new_envp, 's');
}

/**
 * @brief Commande built-in pour sortir une variable de ENV.
 * @param var Variable a unset.
 * @param envp Variable environement
 */
void	ft_unset(char *var, char **envp)
{
	int i = 0, j;
	size_t	len;

	if (!var || !envp)
		return;
	len = 0;
	while (var[len])
		len++;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
		{
			j = i;
			free(envp[i]);
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			return;
		}
		i++;
	}
	printf("Value not exist\n");
	return ;
}
/**
 * @brief Commande built-in pour afficher les varaible de ENV.
 * @param envp Variable d environement.
 */
void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if(ft_strchr(envp[i], '=') != NULL)
			printf("%s\n", envp[i]);
		i++;
	}
}

/**
 * @brief Commande built-in pour terminer l execution.
 * @param arg Possibilite de mettre un argument pour sortir un 
 * code exit specifique.
 */
void	ft_exit(char *arg)
{
	int	status;
	
	status = 0;
	if (arg)
		status = atoi(arg);
	printf("Exiting with code %d\n", status);
	exit(status);
}
