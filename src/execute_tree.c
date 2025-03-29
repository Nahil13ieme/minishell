/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:17:48 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/29 19:16:09 by nbenhami         ###   ########.fr       */
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

static pid_t	execute_pid(t_btree *tree, char **envp, int *fd, int in)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		dup2(fd[in], in);
		if (in == 1)
			close(fd[0]);
		else
			close(fd[1]);
		close(fd[in]);
		tree->child = 1;
		execute_tree(tree, envp);
		exit(tree->status);
	}
	return (pid);
}

static void	execute_pipeline(t_btree *tree, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pid1 = 0;
	pid2 = 0;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if ( tree->left->type != NODE_PIPE)
		pid1 = execute_pid(tree->left, envp, fd, 1);
	if ( tree->right->type != NODE_PIPE)
		pid2 = execute_pid(tree->right, envp, fd, 0);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &tree->left->status, 0);
	waitpid(pid2, &tree->right->status, 0);
	
}

void	execute_tree(t_btree *tree, char **envp)
{
	if (tree == NULL)
		return ;
	if (tree->cmd)
		tree->status = execute_path(tree->cmd, envp, tree->child);
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
		execute_pipeline(tree, envp);
	if (tree->type == NODE_REDIR_IN || tree->type == NODE_REDIR_OUT
		|| tree->type == NODE_APPEND || tree->type == NODE_HEREDOC) 
		execute_redirection(tree, envp);
}
