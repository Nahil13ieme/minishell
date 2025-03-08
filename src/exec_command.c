/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:59:24 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/07 15:59:24 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_command(char **command, char **env)
{
	char	*path;
	char	*token;
	char	*cmd_path;
	char	*full_path;

	if (access(command[0], X_OK) == 0)
	{
		execve(command[0], command, env);
		perror("execve");
		return ;
	}
	path = getenv("PATH");
	token = ft_strtok(path, ":");
	while (token != NULL)
	{
		cmd_path = ft_strjoin(token, "/");
		full_path = ft_strjoin(cmd_path, command[0]);
		free(cmd_path);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, command, env);
			perror("execve");
			free(full_path);
			return ;
		}
		free(full_path);
		free(token);
		token = ft_strtok(NULL, ":");
	}
	ft_putstr_fd(command[0], 2);
	ft_putstr_fd( ": command not found", 2);
	ft_putchar_fd('\n', 2);
	(void)env;
	(void)command;
}
