/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:48:08 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/14 18:16:15 by nbenhami         ###   ########.fr       */
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

char	*handle_token(char *line, char **env, int *i)
{
	char	*current_token;
	char	*segment;
	char	*temp;
	
	current_token = ft_strdup("");
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n')
	{
		segment = NULL;
		if (line[*i] == '\'')
			segment = extract_quote(line, i, '\'');
		else if (line[*i] == '"')
			segment = handle_double_quote(line, i, env);
		else if (line[*i] == '$')
			segment = expand_variable(line + *i, i, env);
		else
			segment = extract_segment(line, i);
		if (!segment)
			{
				if (current_token)
					free(current_token);
				return (NULL);
			}
		if (segment && segment[0] != '\0')
		{
			if (current_token)
			{
				temp = ft_strjoin(current_token, segment);
				free(current_token);
				free(segment);
				if (!temp)
					return (NULL);
				current_token = temp;
			} 
			else
				current_token = segment;
		}
		else if (segment)
			free(segment);
	}
	return (current_token);
}

char **tokenizer(char *line, char **env)
{
	char	**tokens;
	int		i;
	int		len;
	char	*current_token;

	tokens = NULL;
	len = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		if (line[i] == '\0')
			break ;
		current_token = handle_token(line, env, &i);
		if (!current_token)
			return (ft_free_split(tokens), NULL);
		if (current_token)
		{
			len++;
			tokens = ft_realloc(tokens, (len + 1) * sizeof(char *), len * sizeof(char *));
			if (!tokens)
				return (free(current_token), NULL);
			tokens[len - 1] = current_token;
			tokens[len] = NULL;
		}
	}
	return (tokens);
}

void	parse_line(char *line, char ***env)
{
	char	**command;
	int		status;

	command = tokenizer(line, *env);
	if (!command)
		return ;
	else if (command)
	{
		if (check_builtins(command[0]))
			exec_builtins(command, env);
		else
			parse_exec_command(command, *env, &status);
		ft_free_split(command);
	}
	else
	{
		ft_putstr_fd("Error: Invalid command\n", 2);
		ft_free_split(command);
	}
}
