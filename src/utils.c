/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:17:41 by tle-saut          #+#    #+#             */
/*   Updated: 2025/03/25 17:54:11 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_env(char **envp)
{
	int	i;
	char	**cpy_env;
	
	i = 0;
	while (envp[i])
		i++;
	cpy_env = malloc(sizeof(char *) * i + 1);
	if (cpy_env == NULL)
		return (0);
	i = 0;
	while (envp[i])
		{
			cpy_env[i] = ft_strdup(envp[i]);
			if (cpy_env[i] == NULL)
				{
					free_tab(cpy_env);
					break ;
				}
			i++;
		}
	cpy_env[i] = NULL;
	return (cpy_env);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	free(tab);
}
