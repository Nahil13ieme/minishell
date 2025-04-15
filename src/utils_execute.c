/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:18:23 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/15 11:44:32 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	execute_and(t_btree *tree)
{
	execute_tree(tree->left);
	if (tree->left->status == 0)
	{
		execute_tree(tree->right);
		if (tree->right->status == 0)
			tree->status = 0;
		else
			tree->status = -1;
	}
	else
		tree->status = -1;
}

static void	execute_or(t_btree *tree)
{
	execute_tree(tree->left);
	if (tree->left->status != 0)
	{
		execute_tree(tree->right);
		if (tree->right->status != 0)
			tree->status = -1;
		else
			tree->status = 0;
	}
	else
		tree->status = 0;
}

void	ft_if_execute_andor(t_btree *tree)
{
	if (g_signal == SIGINT)
		return ;
	if (tree->type == NODE_AND)
		execute_and(tree);
	else if (tree->type == NODE_OR)
		execute_or(tree);
}
