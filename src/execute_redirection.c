/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:56:35 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/01 17:42:18 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	execute_redir_in(t_btree *tree, char **envp)
{
	int	fd;
	int	saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		exit_error("dup");
	fd = open(tree->right->cmd[0], O_RDONLY);
	if (fd == -1)
		exit_error("open");
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_error("dup2");
	close(fd);
	execute_tree(tree->left, envp);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdin);
}

static void	execute_redir_out(t_btree *tree, char **envp)
{
	int	fd;
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		exit_error("dup");
	fd = open(tree->right->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_error("open");
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_error("dup2");
	close(fd);
	execute_tree(tree->left, envp);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdout);
}

static void	execute_append(t_btree *tree, char **envp)
{
	int	fd;
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		exit_error("dup");
	fd = open(tree->right->cmd[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit_error("open");
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit_error("dup2");
	close(fd);
	execute_tree(tree->left, envp);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdout);
}

static void	execute_heredoc(t_btree *tree, char **envp)
{
	char	*line;
	char	**cmd;
	int		i;

	i = 0;
	line = NULL;
	cmd = malloc(sizeof(char *) * 1);
	if (!cmd)
		exit_error("malloc");
	cmd[0] = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_memcmp(line, tree->right->cmd[0], ft_strlen(tree->right->cmd[0])) == 0)
			break;
		cmd[i] = ft_strdup(line);
		if (!cmd[i])
			exit_error("malloc");
		i++;
		cmd = ft_realloc(cmd, sizeof(char *) * (i + 1), sizeof(char *) * (i));
		cmd[i] = NULL;
		free(line);
		line = NULL;
	}
	free(line);
	(void)envp;
}

void	execute_redirection(t_btree *tree, char **envp)
{
	if (tree->type == NODE_REDIR_IN)
		execute_redir_in(tree, envp);
	else if (tree->type == NODE_REDIR_OUT)
		execute_redir_out(tree, envp);
	else if (tree->type == NODE_APPEND)
		execute_append(tree, envp);
	else if (tree->type == NODE_HEREDOC)
		execute_heredoc(tree, envp);
}
