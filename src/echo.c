/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:49:05 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/15 01:33:13 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_echo(t_exec *exec)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	t_cmd	*command = exec->scmds[0];
	if (command->argc > 1 && ft_strncmp(command->cmd[1], "-n", 3) == 0)
	{
		n = 1;
		i++;
	}
	while(i < command->argc)
	{
		ft_putstr_fd(command->cmd[i], 1);
		if (i + 1 < command->argc)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
	exec->status = 0;
}
