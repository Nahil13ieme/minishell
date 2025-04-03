/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:18:23 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 18:09:58 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	execute_and(t_btree *tree, char **envp)
{
	execute_tree(tree->left, envp);
	if (tree->left->status == 0)
	{
		execute_tree(tree->right, envp);
		if (tree->right->status == 0)
			tree->status = 0;
		else
			tree->status = -1;
	}
	else
	{
		tree->status = -1;
		return ;
	}
}

static void	execute_or(t_btree *tree, char **envp)
{
	execute_tree(tree->left, envp);
	if (tree->left->status != 0)
	{
		execute_tree(tree->right, envp);
		if (tree->right->status != 0)
			tree->status = -1;
		else
			tree->status = 0;
	}
	else
	{
		tree->status = 0;
		return ;
	}
}

void	ft_if_execute_andor(t_btree *tree, char **envp)
{
	if (tree->type == NODE_AND)
		execute_and(tree, envp);
	else if (tree->type == NODE_OR)
		execute_or(tree, envp);
}
