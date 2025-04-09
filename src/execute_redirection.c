/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:56:35 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/09 14:09:32 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "minishell.h"

static void execute_append(t_btree *tree);
static void execute_redir_in(t_btree *tree);
static void execute_redir_out(t_btree *tree);

void	exit_error(char *msg)
{
	perror(msg);
	free_glob();
	set_root(NULL, 'f');
	exit(EXIT_FAILURE);
}

static void	execute_redir_in(t_btree *tree)
{
	t_btree *nodes[100];
	int		count;
	t_btree *cmd_node;
	int		saved_stdin;

	cmd_node = tree;
	count = 0;
	while (cmd_node && cmd_node->type == NODE_REDIR_IN)
	{
		nodes[count++] = cmd_node;
		cmd_node = cmd_node->left;
	}
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		exit_error("dup");
	open_fd(count, nodes, O_RDONLY, STDIN_FILENO);
	if (cmd_node)
		execute_tree(cmd_node);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdin);
}

static void execute_redir_out(t_btree *tree)
{
	t_btree *nodes[100];
	int		count;
	t_btree *cmd_node;
	int		saved_stdout;

	cmd_node = tree;
	count = 0;
	while (cmd_node && (cmd_node->type == NODE_APPEND || cmd_node->type == NODE_REDIR_OUT))
	{
		if (cmd_node->type == NODE_APPEND)
		{
			execute_append(cmd_node);
			return ;
		}
		nodes[count++] = cmd_node;
		cmd_node = cmd_node->left;
	}
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		exit_error("dup");
	open_fd(count, nodes, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
	if (cmd_node)
		execute_tree(cmd_node);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdout);
	tree->status = 0;
}


void open_fd(int count, t_btree * nodes[100], int o_flags, int std)
{
	int i;
	int fd;

	i = count - 1;
	while (i >= 0)
	{
		fd = open(nodes[i]->file, o_flags, 0644);
		if (fd == -1)
			exit_error("open");
		
		if (dup2(fd, std) == -1)
			exit_error("dup2");
		close(fd);
		i--;
	}
}

static void	execute_append(t_btree *tree)
{
	t_btree *nodes[100];
	int		count;
	t_btree *cmd_node;
	int		saved_stdout;

	cmd_node = tree;
	count = 0;
	while (cmd_node && (cmd_node->type == NODE_APPEND || cmd_node->type == NODE_REDIR_OUT))
	{
		if (cmd_node->type == NODE_REDIR_OUT)
		{
			execute_redir_out(cmd_node);
			return ;
		}
		nodes[count++] = cmd_node;
		cmd_node = cmd_node->left;
	}
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		exit_error("dup");
	open_fd(count, nodes, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
	if (cmd_node)
		execute_tree(cmd_node);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdout);
}

void	execute_redirection(t_btree *tree)
{
	if (tree->type == NODE_REDIR_IN)
		execute_redir_in(tree);
	else if (tree->type == NODE_REDIR_OUT)
		execute_redir_out(tree);
	else if (tree->type == NODE_APPEND)
		execute_append(tree);
	else if (tree->type == NODE_HEREDOC)
		execute_heredoc(tree);
}
