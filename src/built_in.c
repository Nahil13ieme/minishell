/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:51:42 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/14 13:48:55 by tle-saut         ###   ########.fr       */
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
