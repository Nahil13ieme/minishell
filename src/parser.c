/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:48:08 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/14 23:16:54 by nbenhami         ###   ########.fr       */
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

static void skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
		*i += 1;
}

static char **realloc_cmd(char **cmd, int old_size, int new_size)
{
	char	**new_cmd;

	new_cmd = ft_realloc(cmd, new_size * sizeof(char *), old_size * sizeof(char *));
	return (new_cmd);
}

void tokenizer(char *line, char **env, t_exec *exec)
{
	int		i;
	t_cmd	*command;

	i = 0;
	command = exec->scmds[exec->nbr_cmds];
	skip_spaces(line, &i);
	while (line[i])
	{
		if (command->argc + 1 >= command->avac)
		{
			command->avac += 10;
			command->cmd = realloc_cmd(command->cmd, command->avac - 10, command->avac);
			if (!command->cmd)
				return ;
		}
		command->cmd[command->argc] = handle_token(line, env, &i);
		if (!command->cmd[command->argc])
			return ;
		command->argc += 1;
		command->cmd[command->argc] = NULL;
		skip_spaces(line, &i);
		if (!line[i])
			break ;
	}
}

void	parse_line(char *line, char ***env)
{
	t_exec	*exec;

	exec = init_exec();
	if (!exec)
		return ;
	exec->scmds[0] = init_command();
	if (!exec->scmds[0])
	{
		free(exec->scmds);
		free(exec);
		return ;
	}
	tokenizer(line, *env, exec);
	for (int i = 0; i < exec->scmds[0]->argc; i++)
	{
		printf("Command %d: %s\n", i, exec->scmds[0]->cmd[i]);
	}
	for (int i = 0; i < exec->nbr_cmds + 1; i++)
	{
		if (check_builtins(exec->scmds[i]->cmd[0]) == 1)
		{
			exec_builtins(exec->scmds[i]->cmd, env);
			break ;
		}
		else
		{
			parse_exec_command(exec->scmds[i]->cmd, *env, &exec->status);
			if (exec->status != 0)
				break ;
		}
	}
	free_exec(exec);
}
