/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:17:41 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 18:29:21 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_print_env(int export)
{
	char	**tab;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (export == 0)
		tab = sim_glob(NULL, 'g');
	if (export == 1)
		tab = sim_glob(NULL, 'G');
	while (tab[i])
	{
		j = 0;
		if (export == 0)
			if (ft_strchr(tab[i], '=') != NULL)
				printf("%s\n", tab[i]);
		if (export == 1)
		{
			ft_while_print_export(tab, i, j);
		}
		i++;
	}
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
