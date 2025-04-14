/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:16:39 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 20:17:53 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_redirection(t_btree *tree)
{
	return (tree->type == NODE_REDIR_IN
		|| tree->type == NODE_REDIR_OUT
		|| tree->type == NODE_APPEND
		|| tree->type == NODE_HEREDOC);
}

static void	extract_nodes(t_btree *tree,
	t_btree **cmd_node, t_btree *nodes[100], int *count)
{
	*cmd_node = tree;
	*count = 0;
	while (*cmd_node && is_redirection(*cmd_node))
	{
		nodes[(*count)++] = *cmd_node;
		*cmd_node = (*cmd_node)->left;
	}
}

static int	execute(t_btree *tree)
{
	t_btree	*nodes[100];
	int		count;
	t_btree	*cmd_node;
	int		in2;
	int		out2;

	count = 0;
	extract_nodes(tree, &cmd_node, nodes, &count);
	in2 = dup(STDIN_FILENO);
	out2 = dup(STDOUT_FILENO);
	if (in2 == -1 || out2 == -1)
		exit_error("dup");
	if (open_fd(count, nodes) == -1)
	{
		if (dup2(in2, STDIN_FILENO) == -1 || dup2(out2, STDOUT_FILENO) == -1)
			exit_error("dup2");
		return (close(in2), close(out2), 1);
	}
	if (cmd_node)
		execute_tree(cmd_node);
	tree->status = cmd_node->status;
	if (dup2(in2, STDIN_FILENO) == -1 || dup2(out2, STDOUT_FILENO) == -1)
		exit_error("dup2");
	return (close(in2), close(out2), 0);
}

int	get_std(t_btree *node)
{
	int	std;

	if (node->type == NODE_REDIR_IN || node->type == NODE_HEREDOC)
		std = STDIN_FILENO;
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_APPEND)
		std = STDOUT_FILENO;
	else
		std = -1;
	return (std);
}

void	execute_redirection(t_btree *tree)
{
	if (tree->type == NODE_REDIR_OUT || tree->type == NODE_APPEND)
		execute(tree);
	else if (tree->type == NODE_REDIR_IN)
		execute(tree);
	else if (tree->type == NODE_HEREDOC)
		execute_heredoc(tree);
}