/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:14:43 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/29 20:29:02 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Creer un noeud de l'arbre binaire.
 * @type : type du noeud
 * @left : fils gauche
 * @right : fils droit
 * @cmd : commande
 * @return : le noeud cree
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
	node->child = 0;
	node->status = 0;
	return (node);
}

void	free_tree(t_btree *root)
{
	int	i;

	if (!root)
		return ;
	i = 0;
	free_tree(root->left);
	free_tree(root->right);
	if (root->cmd)
	{
		while (root->cmd[i])
		{
			if (root->cmd[i])
				free(root->cmd[i]);
			i++;
		}
		free(root->cmd);
		root->cmd = NULL;
	}
	free(root);
}
