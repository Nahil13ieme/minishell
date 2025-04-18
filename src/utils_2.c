/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:10:31 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/14 19:34:30 by nbenhami         ###   ########.fr       */
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
		if (ft_sort(tab[i], tab[i + 1]) == 1)
		{
			swap_tab(&tab[i], &tab[i + 1]);
			i = 0;
		}
		i++;
	}
	ft_print_env(tab, 1);
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

int	ft_sort(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (str1[i] > str2[i])
		return (1);
	else
		return (0);
}
