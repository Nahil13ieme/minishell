/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:17:48 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/09 15:58:29 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static pid_t	execute_pid(t_btree *tree, int *fd, int fileno)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit_error("fork");
	else if (pid == 0)
	{
		setup_child_signals();
		if (dup2(fd[fileno], fileno) == -1)
			exit_error("dup2");
		if (fileno == 1)
			close(fd[0]);
		else
			close(fd[1]);
		close(fd[fileno]);
		tree->child = 1;
		execute_tree(tree);
		status = tree->status;
		set_root(NULL, 'f');
		free_glob();
		exit(status);
	}
	return (pid);
}

static void	execute_pipeline(t_btree *tree)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pid1 = 0;
	pid2 = 0;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = execute_pid(tree->left, fd, STDOUT_FILENO);
	pid2 = execute_pid(tree->right, fd, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &tree->status, 0);
	waitpid(pid2, &tree->status, 0);
	if (WIFEXITED(tree->status))
		tree->status = WEXITSTATUS(tree->status);
}

static char	*handle_word2(char *line, int *i)
{
	char	*segment;
	int		start;
	int		len;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i])
		&& line[*i] != '<' && line[*i] != '>'
		&& line[*i] != ';' && line[*i] != '|'
		&& !(line[*i] == '&' && line[(*i) + 1] == '&')
		&& line[*i] !='\''
		&& line[*i] != '\"' && line[*i] != '$')
		(*i)++;
	len = *i - start;
	segment = ft_substr(line, start, len);
	if (!segment)
	{
		perror("substr");
		exit(EXIT_FAILURE);
	}
	(*i)--;
	return (segment);
}

static char	**retrieve_var(char **cmd)
{
	char	*segment;
	char	*tmp = NULL;
	char	*word;
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		line = cmd[i];
		segment = NULL;
		while (line[j] && line[j] != ' ')
		{
			if (line[j] == '$')
				word = handle_env_variable(line, &j);
			else if (line[j] == '\'' || line[j] == '"')
				word = handle_quoted_string(line, &j);
			else if (line[j] != '<' && line[j] != '>'
				&& line[j] != ';' && line[j] != '|'
				&& (line[j] != '&' || line[j + 1] != '&'))
				word = handle_word2(line, &j);
			else
				break ;
			if (!word)
				return (NULL);
			j++;
			tmp = segment;
			segment = ft_strjoin(segment, word);
				free(word);
			free(tmp);
		}
		free(line);
		cmd[i] = ft_strdup(segment);
		free(segment);
		i++;
	}
	return (cmd);
}

void	execute_tree(t_btree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->cmd)
	{
		if (tree->cmd && strcmp(tree->cmd[0], "$?") == 0)
		{
			free(tree->cmd[0]);
			tree->cmd[0] = ft_itoa(get_exit_code());
		}
		tree->cmd = retrieve_var(tree->cmd);
		execute_path(tree);
	}
	ft_if_execute_andor(tree);
	if (tree->type == NODE_SEMICOLON)
	{
		execute_tree(tree->left);
		execute_tree(tree->right);
		tree->status = tree->right->status;
	}
	if (tree->type == NODE_PIPE)
		execute_pipeline(tree);
	if (tree->type == NODE_REDIR_IN || tree->type == NODE_REDIR_OUT
		|| tree->type == NODE_APPEND || tree->type == NODE_HEREDOC)
		execute_redirection(tree);
	set_exit_code(tree->status);
}
