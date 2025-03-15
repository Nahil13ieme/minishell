/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:47:04 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/15 01:42:45 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cd(t_exec *exec)
{
	t_cmd	*command;

	command = exec->scmds[0];
	exec->status = 0;
	if (command->argc == 1)
	{
		if (chdir(getenv("HOME")) == -1)
		{
			exec->status = 1;
			perror("cd");
		}
	}
	else if (command->argc == 2)
	{
		if (chdir(command->cmd[1]) == -1)
		{
			exec->status = 1;
			perror("cd");
		}
	}
	else
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		exec->status = 1;
	}
}
