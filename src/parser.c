/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:48:08 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/11 21:20:53 by nbenhami         ###   ########.fr       */
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

static char	*extract_quote(char *line, int *i, char quote)
{
	int		start;
	char	*ret;
	int		len;

	start = *i + 1;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
	{
		len = *i - start;
		ret = ft_substr(line, start, len);
		(*i)++;
		return (ret);
	}
	perror("unclosed quote");
	return (NULL);
}

static char	*expand_variable(char *line)
{
	char	*var_name;
	char	*var_value;

	var_name = line + 1;
	var_value = getenv(var_name);
	if (var_value)
	{
		return (ft_strdup(var_value));
	}
	else
	{
		perror("variable not found");
		return (NULL);
	}
}

static void	handle_double_quote(char **temp, char *line, int *i)
{
	char *expanded;

	*temp = extract_quote(line, i, '"');
	if (!*temp)
	{
		return ;
	}
	if (ft_strchr(*temp, '$'))
	{
		expanded = expand_variable(*temp);
		free(*temp);
		*temp = expanded;
	}
	
}

char	**tokenizer(char *line, char **env)
{
	char	**tokens;
	char	*temp;
	int		i;
	int		len;

	(void)env;
	tokens = NULL;
	i = 0;
	len = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		if (line[i] == '\0')
			break;
		if (line[i] == '\'')
		{
			temp = extract_quote(line, &i, '\'');
			if (!temp)
				return (ft_free_split(tokens), NULL);
		}
		else if (line[i] == '"')
		{
			handle_double_quote(&temp, line, &i);
			if (!temp)
				return (ft_free_split(tokens), NULL);
		}
		else if (line[i] == '$')
		{
			temp = expand_variable(line + i);
			if (!temp)
				return (ft_free_split(tokens), NULL);
			i += ft_strlen(temp) - 1;
		}
		else if (line[i] == '|')
		{
			temp = ft_strdup("|");
			if (!temp)
				return (ft_free_split(tokens), NULL);
			i++;
		}
		else
		{
			int start = i;
			while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
					&& line[i] != '\'')
				i++;
			if (i > start)
			{
				temp = ft_substr(line, start, i - start);
				if (!temp)
				return (ft_free_split(tokens), NULL);
			}
			else
				continue;
		}
		if (temp && temp[0] == '\0')
		{
			free(temp);
			continue;
		}
		len++;
		tokens = ft_realloc(tokens, (len + 1) * sizeof(char *), len * sizeof(char *));
		if (!tokens)
			return (free(temp), NULL);
		tokens[len - 1] = temp;
		tokens[len] = NULL;
	}
	return (tokens);
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

	command = tokenizer(line, env);
	for(int i = 0; command[i]; i++)
		printf("command : %s\n", command[i]);
	if (command)
	{
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
	else
	{
		ft_putstr_fd("Error: Invalid command\n", 2);
	}
}
