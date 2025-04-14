/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:25:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 19:34:51 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
