/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:48:08 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/12 21:01:16 by nbenhami         ###   ########.fr       */
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

static char	*expand_variable(char *line, int *i, char **env)
{
	char	*var_name;
	char	*var_value;
	char	*result;
	char	*temp;
	int		start;
	int		len;

	start = 0;
	result = ft_strdup("");
	(void)i;
	while (line[start])
	{
		len = 0;
		if (line[start] == '$' && line[start + 1] != 0 && line[start + 1] != ' '
			&& line[start + 1] != '\n' && line[start + 1] != '\t')
		{
			start++;
			while (line[start] && (ft_isalnum(line[start]) || line[start] == '_'))
			{
				len++;
				start++;
			}
			var_name = ft_substr(line, start - len, start - 1);
			printf("var_name = %s\n", var_name);
			var_value = get_my_env(env, var_name);
			printf("var_value = %s\n", var_value);
			temp = ft_strdup(var_value);
			free(var_name);
		}
		if (temp)
		{
			printf("temp = %s\n", temp);
			result = ft_strjoin(result, temp);
			free(temp);
		}
		start++;
	}
	printf("result = %s\n", result);
	return (result);
}

static void	handle_double_quote(char **temp, char *line, int *i, char **env)
{
	char	*expanded;
	int		start = *i;

	*temp = extract_quote(line, i, '"');
	if (!*temp)
		return ;
	if (ft_strchr(*temp, '$'))
	{
		expanded = expand_variable(*temp, &start, env);
		free(*temp);
		*temp = expanded;
	}
}

char **tokenizer(char *line, char **env)
{
	char **tokens = NULL;
	int i = 0;
	int len = 0;

	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		if (line[i] == '\0')
			break;
		char *current_token = NULL;
		while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			char *segment = NULL;
			
			if (line[i] == '\'')
			{
				segment = extract_quote(line, &i, '\'');
				if (!segment)
				{
					if (current_token)
						free(current_token);
					return (ft_free_split(tokens), NULL);
				}
			}
			else if (line[i] == '"')
			{
				handle_double_quote(&segment, line, &i, env);
				if (!segment)
				{
					if (current_token)
						free(current_token);
					return (ft_free_split(tokens), NULL);
				}
			}
			else if (line[i] == '$')
			{
				segment = expand_variable(line + i, &i, env);
				if (!segment)
				{
					if (current_token)
						free(current_token);
					return (ft_free_split(tokens), NULL);
				}
			}
			else
			{
				segment = extract_segment(line, &i, current_token, tokens);
			}
			if (segment && segment[0] != '\0')
			{
				if (current_token)
				{
					char *temp = ft_strjoin(current_token, segment);
					free(current_token);
					free(segment);
					if (!temp)
						return (ft_free_split(tokens), NULL);
					current_token = temp;
				}
				else
				{
					current_token = segment;
				}
			}
			else if (segment)
			{
				free(segment);
			}
		}
		if (current_token && current_token[0] != '\0')
		{
			len++;
			tokens = ft_realloc(tokens, (len + 1) * sizeof(char *), len * sizeof(char *));
			if (!tokens)
			{
				free(current_token);
				return (NULL);
			}
			tokens[len - 1] = current_token;
			tokens[len] = NULL;
		}
		else if (current_token)
		{
			free(current_token);
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
		{
			exec_builtins(command, env);
		}
		else
		{
			parse_exec_command(command, *env, &status);
		}
		ft_free_split(command);
	}
	else
	{
		ft_putstr_fd("Error: Invalid command\n", 2);
	}
}
