/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:54:41 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/10 15:59:49 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_exit_code(int code)
{
	sim_exit(code, 's');
}

int	get_exit_code(void)
{
	return (sim_exit(0, 'g'));
}

int	sim_exit(int code, char c)
{
	static int	global = 0;

	if (c == 'g')
		return (global);
	else
		global = code;
	return (0);
}

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
 * @brief Commande built-in pour terminer l execution.
 * @param arg Possibilite de mettre un argument pour sortir un 
 * code exit specifique.
 */
void	ft_exit(t_btree *tree)
{
	int	status;

	status = 0;
	if (tree->cmd[1])
	{
		status = ft_atoi(tree->cmd[1]);
		if (check_alpha(tree->cmd[1]))
		{
			ft_fprintf("minishell: exit: %s: numeric argument required\n",
				tree->cmd[1]);
			tree->status = 2;
			return ;
		}
	}
	else
		status = get_exit_code();
	if (!tree->child)
		printf("exit\n");
	if (tree->cmd[1] && tree->cmd[2] != NULL)
	{
		ft_fprintf("minishell: exit: too many arguments\n");
		tree->status = 1;
		return ;
	}
	sim_glob(NULL, 'f');
	set_root(NULL, 'f');
	exit(status);
}
