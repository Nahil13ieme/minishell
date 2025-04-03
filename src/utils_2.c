/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:10:31 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 18:13:15 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap_tab(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	print_sort_export(void)
{
	int		i;
	int		size;
	char	**tab;

	tab = sim_glob(NULL, 'G');
	size = 0;
	i = 0;
	while (tab[size])
		size++;
	while (i < size - 1)
	{
		if (tab[0][0] > tab[1][0])
			i = 0;
		if ((tab[i][0]) > (tab[i + 1][0]))
		{
			swap_tab(&tab[i], &tab[i + 1]);
			i = 0;
		}
		i++;
	}
	sim_glob(tab, 'S');
	ft_print_env(1);
}

void	set_export(void)
{
	char	**env;
	char	**cpy;
	int		i;

	env = sim_glob(NULL, 'g');
	cpy = malloc(sizeof(char *) * (ft_tablen(env) + 1));
	i = 0;
	while (env[i])
	{
		cpy[i] = env[i];
		i++;
	}
	env = sim_glob(NULL, 'G');
	free(env);
	sim_glob(cpy, 'S');
}

void	modifi_env_export(char *var)
{
	char	*equal_pos;
	char	**envi;
	char	**export;

	equal_pos = ft_strchr(var, '=');
	envi = sim_glob(NULL, 'g');
	export = sim_glob(NULL, 'G');
	ft_if_modify_export(equal_pos, var, envi, export);
}

void	set_path(void)
{
	char	**envi;
	int		i;
	char	**export;
	char	*cwd;

	i = 0;
	envi = sim_glob(NULL, 'g');
	export = sim_glob(NULL, 'G');
	while (envi[i])
	{
		cwd = getenv("PATH");
		if (ft_strncmp(envi[i], "PATH=", 5) == 0)
		{
			envi[i] = ft_strjoin("PATH=", cwd);
			break ;
		}
		i++;
	}
	i = 0;
	i = ft_while_set_export(export, i);
}
