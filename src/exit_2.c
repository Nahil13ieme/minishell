/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:55:52 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 19:01:15 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !(str[i] == '-'
				|| str[i] == '+'))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Vérifie si l'argument de sortie est valide
 * @param arg L'argument à vérifier
 * @param tree Pointeur vers la structure arborescente
 * @return 1 si l'argument est valide, 0 sinon
 */
static int	check_exit_arg(char *arg, t_btree *tree)
{
	if (check_alpha(arg))
	{
		ft_fprintf("minishell: exit: %s: numeric argument required\n", arg);
		tree->status = 2;
		return (0);
	}
	return (1);
}

/**
 * @brief Commande built-in pour terminer l'exécution.
 * @param tree Pointeur vers la structure arborescente
 */
void	ft_exit(t_btree *tree)
{
	int	status;

	status = 0;
	if (!tree->child)
		printf("exit\n");
	if (tree->cmd[1])
	{
		if (!check_exit_arg(tree->cmd[1], tree))
			return ;
		status = ft_atoi(tree->cmd[1]);
		if (tree->cmd[2] != NULL)
		{
			ft_fprintf("minishell: exit: too many arguments\n");
			tree->status = 1;
			return ;
		}
	}
	else
		status = get_exit_code();
	sim_glob(NULL, 'f');
	set_root(NULL, 'f');
	exit(status % 256);
}
