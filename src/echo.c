/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:49:05 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/09 23:42:26 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_echo(char **command)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (command[1] && command[1][0] == '-')
	{
		if (command[1][1] == 'n' && command[1][2] == '\0')
		{
			i++;
			n = 1;
		}
	}
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
}
