/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:48:08 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/08 01:13:28 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_line(char *line, char **env)
{
	char	**command;
	pid_t	pid;
	int		status;

	command = ft_split(line, ' ');
	if (check_builtins(command[0]))
	{
		exec_builtins(command, env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			exec_command(command, env);
			exit(EXIT_FAILURE);
		} else if (pid > 0)
		{
			waitpid(pid, &status, 0);
		}
		else
		{
			perror("fork");
		}
	}
}