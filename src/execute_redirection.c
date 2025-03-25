/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:56:35 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/25 13:23:13 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	execute_redirection(t_btree *tree, char **envp)
{
	int	fd;
	int	saved_stdin;

	if (tree->type == NODE_REDIR_IN)
	{
		saved_stdin = dup(STDIN_FILENO);
		if (saved_stdin == -1)
			exit_error("dup");
		fd = open(tree->right->cmd[0], O_RDONLY);
		if (fd == -1)
			exit_error("open");
		if (dup2(fd, STDIN_FILENO) == -1)
			exit_error("dup2");
		close(fd);
		execute_tree(tree->left, envp);
		if (dup2(saved_stdin, STDIN_FILENO) == -1)
		exit_error("dup2");
		close(saved_stdin);
	}
	else if (tree->type == NODE_REDIR_OUT)
	{
		saved_stdin = dup(STDOUT_FILENO);
		if (saved_stdin == -1)
			exit_error("dup");
		fd = open(tree->right->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit_error("open");
		if (dup2(fd, STDOUT_FILENO) == -1)
			exit_error("dup2");
		close(fd);
		execute_tree(tree->left, envp);
		if (dup2(saved_stdin, STDOUT_FILENO) == -1)
		exit_error("dup2");
		close(saved_stdin);
	}

}
