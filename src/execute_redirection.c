/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:56:35 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/10 09:56:04 by nbenhami         ###   ########.fr       */
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

static void execute_redir_in(t_btree *tree)
{
	t_btree	*nodes[100];
	int		count;
	t_btree	*cmd_node;
	int		saved_stdin;

	cmd_node = tree;
	count = 0;
	while (cmd_node && (cmd_node->type == NODE_REDIR_IN
		|| cmd_node->type == NODE_HEREDOC || cmd_node->type == NODE_REDIR_OUT))
	{
		nodes[count++] = cmd_node;
		cmd_node = cmd_node->left;
	}
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		exit_error("dup");
	if (open_fd(count, nodes) == -1)
	{
		if (dup2(saved_stdin, STDIN_FILENO) == -1)
			exit_error("dup2");
		close(saved_stdin);
		return ;
	}
	if (cmd_node)
		execute_tree(cmd_node);
	tree->status = cmd_node->status;
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
		nodes[count++] = cmd_node;
		cmd_node = cmd_node->left;
	}
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		exit_error("dup");
	if (open_fd(count, nodes) == -1)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
			exit_error("dup2");
		close(saved_stdout);
		return ;
	}
	if (cmd_node)
		execute_tree(cmd_node);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdout);
	tree->status = 0;
}

static int get_oflags(int type)
{
	if (type == NODE_REDIR_IN)
		return (O_RDONLY);
	else if (type == NODE_REDIR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (type == NODE_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (-1);
}

int	open_fd(int count, t_btree * nodes[100])
{
	int i;
	int fd;
	int pipe_fds[2];
	int	oflags;
	int	std;

	i = count - 1;
	oflags = 0;
	while (i >= 0)
	{
		std = (nodes[i]->type == NODE_REDIR_IN) ? STDIN_FILENO : STDOUT_FILENO;
		oflags = get_oflags(nodes[i]->type);
		if (nodes[i]->type != NODE_HEREDOC)
		{
			fd = open(nodes[i]->file, oflags, 0644);
			if (fd == -1)
			{
				ft_fprintf("minishell: %s: No such file or directory\n", nodes[i]->file);
				nodes[0]->status = 1;
				return (-1);
			}
			if (i == 0)
			{
				if (dup2(fd, std) == -1)
					exit_error("dup2");
				close(fd);
			}
		}
		else
		{
			nodes[i]->heredoc = extract_content_heredoc(nodes[i]->delimiter);
			if (pipe(pipe_fds) == -1)
				exit_error("pipe");
			if (nodes[i]->heredoc)
			{
				int j = 0;
				while (nodes[i]->heredoc[j])
				{
					write(pipe_fds[1], nodes[i]->heredoc[j], ft_strlen(nodes[i]->heredoc[j]));
					write(pipe_fds[1], "\n", 1);
					j++;
				}
			}
			close(pipe_fds[1]);
			if (dup2(pipe_fds[0], std) == -1)
				exit_error("dup2");
			close(pipe_fds[0]);
		}
		i--;
	}
	return (0);
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
		nodes[count++] = cmd_node;
		cmd_node = cmd_node->left;
	}
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		exit_error("dup");
	if (open_fd(count, nodes) == -1)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
			exit_error("dup2");
		close(saved_stdout);
		return ;
	}
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
