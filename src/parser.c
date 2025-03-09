/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:48:08 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/09 17:00:48 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parse_waitpid(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_signal = 0;
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		g_signal = 0;
		return (WTERMSIG(status));
	}
	return (-1);
}

void	parse_exec_command(char **command, char **env, int *status)
{
	pid_t	pid;

	g_signal = -1;
	pid = fork();
	if (pid == 0)
	{
		setup_child_signal();
		exec_command(command, env);
		exit(EXIT_FAILURE);
	} else if (pid > 0)
	{
		*status = parse_waitpid(pid);
		printf("Status: %d\n", *status);
		g_signal = 0;
	}
	else
	{
		perror("fork");
		g_signal = 0;
	}
}

void	parse_line(char *line, char **env)
{
	char	**command;
	int		status;

	command = ft_split(line, ' ');
	if (check_builtins(command[0]))
	{
		exec_builtins(command, env);
	}
	else
	{
		parse_exec_command(command, env, &status);
	}
}
