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

static void	exec_relative(char **command, char **env)
{
	char	*path;
	char	*token;
	char	*cmd_path;
	char	*full_path;

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
			free(token);
			exit(EXIT_FAILURE);
		}
		free(full_path);
		free(token);
		token = ft_strtok(NULL, ":");
	}
}

static void	exec_absolute(char **command, char **env)
{
	if (access(command[0], X_OK) == 0)
	{
		execve(command[0], command, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	exec_command(char **command, char **env)
{
	exec_absolute(command, env);
	exec_relative(command, env);
	perror("execve");
	ft_putstr_fd(command[0], 2);
	ft_putstr_fd( ": command not found", 2);
	ft_putchar_fd('\n', 2);
	exit(127);
}
