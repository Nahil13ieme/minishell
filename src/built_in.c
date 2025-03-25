/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:51:42 by tle-saut          #+#    #+#             */
/*   Updated: 2025/03/25 10:51:34 by tle-saut         ###   ########.fr       */
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

	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}

	while (args[i])
	{
		printf("%s", args[i]);
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
void ft_cd(char *path)
{
	if (!path)
		path = getenv("HOME");
	if (chdir(path) != 0)
		perror("cd");
}

/**
 * @brief Commande built-in pour afficher le chemin actuel
 */
void ft_pwd(void)
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
void ft_export(char *var)
{
	if (!var || !strchr(var, '='))
		return;
	if (putenv(var) != 0)
		perror("export");
}

/**
 * @brief Commande built-in pour sortirune variable de ENV.
 * @param var Variable a de-set.
 */
void ft_unset(char *var)
{
	unsetenv(var);
}

/**
 * @brief Commande built-in pour afficher les varaible de ENV.
 * @param envp Variable d environement.
 */
void ft_env(char **envp)
{
	int i = 0;
	while (envp[i]) {
		printf("%s\n", envp[i]);
		i++;
	}
}

/**
 * @brief Commande built-in pour terminer l execution.
 * @param arg Possibilite de mettre un argument pour sortir un 
 * code exit specifique.
 */
void ft_exit(char *arg)
{
	int status = arg ? atoi(arg) : 0;
	printf("Exiting with code %d\n", status);
	exit(status);
}
