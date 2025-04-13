/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:56:35 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/13 21:20:28 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "minishell.h"

static int	is_redirection(t_btree *tree)
{
	return (tree->type == NODE_REDIR_IN
		|| tree->type == NODE_REDIR_OUT
		|| tree->type == NODE_APPEND
		|| tree->type == NODE_HEREDOC);
}

static void	extract_nodes(t_btree *tree, t_btree **cmd_node, t_btree *nodes[100], int *count)
{

	*cmd_node = tree;
	*count = 0;
	while (*cmd_node && is_redirection(*cmd_node))
	{
		nodes[(*count)++] = *cmd_node;
		*cmd_node = (*cmd_node)->left;
	}
}

static void	execute(t_btree *tree, int std)
{
	t_btree	*nodes[100];
	int		count;
	t_btree	*cmd_node;
	int		saved_fd;

	count = 0;
	extract_nodes(tree, &cmd_node, nodes, &count);
	saved_fd = dup(std);
	if (saved_fd == -1)
		exit_error("dup");
	if (open_fd(count, nodes) == -1)
	{
		if (dup2(saved_fd, std) == -1)
			exit_error("dup2");
		close(saved_fd);
		return ;
	}
	if (cmd_node)
		execute_tree(cmd_node);
	tree->status = cmd_node->status;
	if (dup2(saved_fd, std) == -1)
		exit_error("dup2");
	close(saved_fd);
}

int	open_fd(int count, t_btree *nodes[100])
{
	int	i;
	int	fd;
	int	oflags;
	int	std;

	i = count - 1;
	oflags = 0;
	while (i >= 0)
	{
		std = get_std(nodes[i]);
		oflags = get_oflags(nodes[i]->type);
		if (nodes[i]->type != NODE_HEREDOC)
		{
			if (ft_strlen(nodes[i]->file) >= 256)
			{
				ft_fprintf("minishell: %s: File name too long\n",
					nodes[i]->file);
				nodes[0]->status = 1;
				return (-1);
			}
			else if (check_dir_file(nodes[i]->file) == 1)
			{
				nodes[0]->status = 1;
				return (-1);
			}
			fd = open(nodes[i]->file, oflags, 0644);
			if (fd == -1)
			{
				if (errno == EACCES)
					ft_fprintf("minishell: %s: Permission denied\n",
						nodes[i]->file);
				else if (errno == ENOENT)
					ft_fprintf("minishell: %s: No such file or directory\n",
						nodes[i]->file);
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
			apply_heredoc(nodes[i], 0);
		i--;
	}
	return (0);
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
		execute(tree, STDOUT_FILENO);
	else if (tree->type == NODE_REDIR_IN)
		execute(tree, STDIN_FILENO);
	else if (tree->type == NODE_HEREDOC)
		execute_heredoc(tree);
}
