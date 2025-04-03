/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:11:42 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 15:59:48 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	printf("%d\n", status);
	exit(status);
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
		if (ft_strchr(envp[i], '=') != NULL)
			printf("%s\n", envp[i]);
		i++;
	}
}
