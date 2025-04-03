/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:24:58 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 14:25:36 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_tree(t_btree tree)
{
	int	i;

	i = 0;
	if (tree.left)
		print_tree(*tree.left);
	if (tree.cmd)
	{
		while (tree.cmd[i])
		{
			printf("%s ", tree.cmd[i]);
			i++;
		}
		printf("\n");
	}
	if (tree.right)
		print_tree(*tree.right);
}

t_btree	*set_root(t_btree *root, char c)
{
	static t_btree	*global_tree = NULL;

	if (c == 's')
	{
		if (global_tree)
			free_tree(global_tree);
		global_tree = root;
	}
	else if (c == 'g')
	{
		if (global_tree)
			return (global_tree);
		else
			return (NULL);
	}
	else if (c == 'f')
	{
		free_tree(global_tree);
		global_tree = NULL;
	}
	return (NULL);
}
