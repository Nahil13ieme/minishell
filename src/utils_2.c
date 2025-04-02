/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:10:31 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/02 16:23:31 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap_tab(char **a, char **b)
{
	char *temp;

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

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return(i);
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
	int		i;
	char	**envi;
	char	**export;
	equal_pos = ft_strchr(var, '=');
	i = 0;
	envi = sim_glob(NULL, 'g');
	export = sim_glob(NULL, 'G');
	if (equal_pos)
	{
		while (envi[i])
		{
			if (ft_strncmp(envi[i], var, equal_pos - var) == 0)
			{
				free(envi[i]);
				return;
			}
			i++;
		}
	}
	else
	{
		while (export[i])
		{
			if (ft_strncmp(export[i], var, ft_strlen(export[i])) == 0)
			{
				free(export[i]);
				return;
			}
			i++;
		}
	}
	
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
			cwd = getcwd(NULL, 0);
			if (ft_strncmp(envi[i], "PATH=", 5) == 0)
			{
				free(envi[i]);
				envi[i] = ft_strjoin("PATH=", cwd);
				free(cwd);
				break ;
			}
			free(cwd);
			i++;
		}
		i = 0;
		while (export[i])
		{
			cwd = getcwd(NULL, 0);
			if (ft_strncmp(export[i], "PWD=",4) == 0)
			{
				free(export[i]);
				export[i] = ft_strjoin("PWD=",cwd);
				free(cwd);
				return;
			}
			free(cwd);
			i++;
		}
}
