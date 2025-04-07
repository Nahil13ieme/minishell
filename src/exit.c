/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:54:41 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/07 10:57:17 by nbenhami         ###   ########.fr       */
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
	else
		status = get_exit_code();
	printf("exit\n");
	sim_glob(NULL, 'f');
	set_root(NULL, 'f');
	exit(status);
}
