/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:48:08 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/10 01:54:09 by nbenhami         ###   ########.fr       */
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
	}
	else if (pid > 0)
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

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*	We splitting the line into command variable.
	Then we need to read some docs to see what we should do.
	Like the line contain a | we should redirect the output.
	1 - Lexical analysis and parsing
	2 - Brace Expansion
	3 - Tilde Expansion
	4 - Parameter Expansion
	5 - Command Substitution
	6 - Arithmetic Expansion
	7 - Process Substitution
	8 - Word Splitting
	9 - Filename Expansion
	10 - Quote
	11 - Redirection
	12 - Function Definition
	13 - Command Execution
*/
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
	ft_free_split(command);
}
