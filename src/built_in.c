/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:51:42 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/14 18:34:37 by nbenhami         ###   ########.fr       */
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
