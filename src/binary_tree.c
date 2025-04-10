/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:14:43 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/10 05:45:40 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Creer un noeud de l'arbre binaire.
 * @param type : type du noeud
 * @param left : fils gauche
 * @param right : fils droit
 * @param cmd : commande
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
	node->status = 0;
	node->child = 0;
	node->type = type;
	node->cmd = cmd;
	node->left = left;
	node->right = right;
	node->file = NULL;
	node->delimiter = NULL;
	node->heredoc = NULL;
	return (node);
}

void	free_tree(t_btree *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	if (root->cmd)
		free_tab(root->cmd);
	if (root->file)
		free(root->file);
	if (root->delimiter)
		free(root->delimiter);
	if (root->heredoc)
		free_tab(root->heredoc);
	free(root);
}
