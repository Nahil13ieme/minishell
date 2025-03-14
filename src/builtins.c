/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:58:56 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/15 01:35:56 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_builtins(char *command)
{
	if (command == NULL)
		return (0);
	if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}

void	exec_builtins(t_exec *exec, char ***env)
{
	char	**command;

	command = exec->scmds[0]->cmd;
	if (ft_strncmp(command[0], "echo", 5) == 0)
		exec_echo(exec);
	if (ft_strncmp(command[0], "cd", 3) == 0)
		exec_cd(exec);
	if (ft_strncmp(command[0], "pwd", 4) == 0)
		exec_pwd();
	if (ft_strncmp(command[0], "export", 7) == 0)
		exec_export(env, exec);
	if (ft_strncmp(command[0], "unset", 6) == 0)
		exec_unset(exec, env);
	if (ft_strncmp(command[0], "env", 4) == 0)
		exec_env(*env);
	if (ft_strncmp(command[0], "exit", 5) == 0)
		exec_exit(exec);
}
