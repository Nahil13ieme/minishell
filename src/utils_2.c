/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:10:31 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/02 12:27:57 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	swap_tab(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

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