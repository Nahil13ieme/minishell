/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:17:48 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/24 17:44:07 by nbenhami         ###   ########.fr       */
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

static void	execute_and(t_btree *tree, char **envp)
{
	execute_tree(tree->left, envp);
	if (tree->left->status == 0)
	{
		execute_tree(tree->right, envp);
		tree->status = tree->right->status ? -1 : 0;
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
		tree->status = tree->right->status ? -1 : 0;
	}
	else
	{
		tree->status = 0;
		return ;
	}
}

static void execute_pipeline(t_btree *tree, char **envp)
{
	int fd[2];
	pid_t pid1, pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execute_tree(tree->left, envp);
		exit(tree->left->status);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execute_tree(tree->right, envp);
		exit(tree->right->status);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &tree->status, 0);
	waitpid(pid2, &tree->status, 0);
}

void	execute_tree(t_btree *tree, char **envp)
{
	if (tree == NULL)
		return ;
	if (tree->cmd)
		tree->status = execute_path(tree->cmd, envp);
	if (tree->type == NODE_AND)
		execute_and(tree, envp);
	else if (tree->type == NODE_OR)
		execute_or(tree, envp);
	if (tree->type == NODE_SEMICOLON)
	{
		execute_tree(tree->left, envp);
		execute_tree(tree->right, envp);
		tree->status = tree->right->status;
	}
	if (tree->type == NODE_PIPE)
		execute_pipeline(tree,envp);
}
