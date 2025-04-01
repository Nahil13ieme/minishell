/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:10:31 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/01 16:48:19 by toto             ###   ########.fr       */
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
