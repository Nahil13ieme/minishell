/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:10:31 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/10 14:46:01 by tle-saut         ###   ########.fr       */
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

	size = 0;
	i = 0;
	tab = tab_cpy(sim_glob(NULL, 'g'));
	size = ft_tablen(tab);
	while (i < size - 1)
	{
		if (tab[0][0] > tab[1][0])
			i = 0;
		if ((tab[i][0]) > (tab[i + 1][0]))
		{
			if (tab[i + 1])
			{
				swap_tab(&tab[i], &tab[i + 1]);
				i = 0;
			}
		}
		i++;
	}
	ft_print_env(tab, 1);
}

void	set_export(void)
{
	char	**env;
	char	**cpy;
	int		i;
	int		len;

	i = 0;
	env = sim_glob(NULL, 'g');
	len = ft_tablen(env);
	cpy = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len + 1)
	{
		cpy[i] = env[i];
		i++;
	}
	sim_glob(cpy, 'S');
	free(cpy);
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
	char	*cwd;

	i = 0;
	envi = sim_glob(NULL, 'g');
	cwd = NULL;
	while (envi[i])
	{
		cwd = getenv("PATH");
		if (ft_strncmp(envi[i], "PATH=", 5) == 0)
		{
			free(envi[i]);
			envi[i] = ft_strjoin("PATH=", cwd);
			sim_glob(envi, 's');
			break ;
		}
		i++;
	}
}
