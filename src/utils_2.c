/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:10:31 by tle-saut          #+#    #+#             */
/*   Updated: 2025/03/31 16:23:43 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap_tab()

void	print_sort_export(void)
{
	char	**tab;
	int		i;
	char	*decal;
	char	*decalsup;
	int		sorted;

	tab = sim_glob(NULL, 'g');
	sorted = 0;
	i = 0;
	while (tab[i] && sorted == 0)
	{
		sorted = 1;
		decal = ft_strchr(tab[i], 'x');
		decalsup = ft_strchr(tab[i + 1], 'x');
		if ((decal + 2) > (decalsup + 2))
		{
			swap_tab(&tab[i], &tab[i + 1]);
			sorted = 0;
		}
		i++;
	}

}