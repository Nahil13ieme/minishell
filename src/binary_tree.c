/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:14:43 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/25 08:56:29 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Creates a new node in the binary tree.
 * @param type The type of the node.
 * @param cmd The command associated with the node.
 * @param filename The filename associated with the node. can be null.
 * @return A pointer to the newly created node.
 *         Exit if malloc fails.
 */
t_btree	*create_node(t_cmd_type type, t_btree *left, t_btree *right, char **cmd)
{
	t_btree	*node;

	node = malloc(sizeof(t_btree));
	if (!node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->type = type;
	node->cmd = cmd;
	node->left = left;
	node->right = right;
	return (node);
}

void	free_tree(t_btree *root)
{
	int	i;

	i = 0;
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	if (root->cmd)
	{
		while (root->cmd[i])
			free(root->cmd[i++]);
		free(root->cmd);
		root->cmd = NULL;
	}
	root->status = 0;
	free(root);
	root = NULL;
}
