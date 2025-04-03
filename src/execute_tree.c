/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:17:48 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/03 13:58:02 by nbenhami         ###   ########.fr       */
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

static pid_t	execute_pid(t_btree *tree, char **envp, int *fd, int fileno)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork");
	else if (pid == 0)
	{
		if (dup2(fd[fileno], fileno) == -1)
			exit_error("dup2");
		if (fileno == 1)
			close(fd[0]);
		else
			close(fd[1]);
		close(fd[fileno]);
		tree->child = 1;
		execute_tree(tree, envp);
		set_root(NULL, 'f');
		free_glob();
		exit(EXIT_FAILURE);
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
	pid1 = execute_pid(tree->left, envp, fd, STDOUT_FILENO);
	pid2 = execute_pid(tree->right, envp, fd, STDIN_FILENO);
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
	{
		if (tree->cmd && strcmp(tree->cmd[0], "$?") == 0)
		{
			free(tree->cmd[0]);
			tree->cmd[0] = ft_itoa(get_exit_code());
		}
		tree->status = execute_path(tree->cmd, envp, tree->child);
	}
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
	set_exit_code(tree->status);
}
