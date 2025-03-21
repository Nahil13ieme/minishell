/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:17:48 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/21 14:17:01 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_node(t_btree *node)
{
	if (node == NULL)
		return ;
	t_cmd_type type = node->type;
	switch (type)
	{
	case NODE_PIPE:
		printf("Pipe: \n");
		break;
	case NODE_AND:
		printf("And: \n");
		break;
	case NODE_OR:
		printf("Or: \n");
		break;
	case NODE_SEMICOLON:
		printf("Semicolon: \n");
		break;
	case NODE_REDIR_IN:
		printf("Redirect In: \n");
		break;
	case NODE_REDIR_OUT:
		printf("Redirect Out: \n");
		break;
	case NODE_HEREDOC:
		printf("Heredoc: \n");
		break;
	case NODE_APPEND:
		printf("Append: \n");
		break;
	default:
		break;
	}
}

void	execute_tree(t_btree *tree, char **envp)
{
	int	ret;
	if (tree == NULL)
		return ;
	print_node(tree);
	if (tree->left)
		execute_tree(tree->left, envp);
	
	if (tree->left && tree->left->cmd && tree->left->cmd[0])
		printf("-> %s \t", tree->left->cmd[0]);
	else if (tree->left)
	{
		printf("-> ");
		print_node(tree->left);
		printf("\t");
	}
	if (tree->cmd)
	{
		ret = execute_path(tree->cmd, envp);
		printf("ret = %d\n", ret);
	}
	if (tree->right)
		execute_tree(tree->right, envp);
}