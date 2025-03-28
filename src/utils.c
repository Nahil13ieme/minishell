/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:17:41 by tle-saut          #+#    #+#             */
/*   Updated: 2025/03/26 15:29:50 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_env(char **envp)
{
	int		i;
	char	**cpy_env;
	
	i = 0;
	while (envp[i])
		i++;
	cpy_env = malloc(sizeof(char *) * (i + 1));
	if (cpy_env == NULL)
		return ;
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
	sim_glob(cpy_env, 's');
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
char	**sim_glob(char **tab, char c)
{
	static char **glob = NULL;

	if (c == 'g')
		return (glob);
	else
		glob = tab;
	return NULL;
}

char	**ft_tab_realloc(char **tab, size_t new_size)
{
	size_t old_size = 0;
	char **new_tab;
	size_t i = 0;

	while (tab && tab[old_size])
		old_size++;
	new_tab = (char **)malloc(sizeof(char *) * (old_size + new_size + 1));
	if (!new_tab)
		return NULL;
	while (i < old_size)
	{
		new_tab[i] = tab[i];
		i++;
	}
	while (i < old_size + new_size)
	{
		new_tab[i] = NULL;
		i++;
	}
	new_tab[i] = NULL;
	free(tab);
	return new_tab;
}

void	ft_print_env(char **envp)
{
	int i = 0;

	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

