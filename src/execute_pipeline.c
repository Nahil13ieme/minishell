/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:12:27 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 19:46:41 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static pid_t	execute_pid(t_btree *tree, int *fd, int fileno)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit_error("fork");
	else if (pid == 0)
	{
		setup_child_signals();
		if (dup2(fd[fileno], fileno) == -1)
			exit_error("dup2");
		if (fileno == 1)
			close(fd[0]);
		else
			close(fd[1]);
		close(fd[fileno]);
		tree->child = 1;
		execute_tree(tree);
		status = tree->status;
		set_root(NULL, 'f');
		free_glob();
		exit(status);
	}
	return (pid);
}

void	execute_pipeline(t_btree *tree)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pid1 = 0;
	pid2 = 0;
	if (pipe(fd) == -1)
		exit_error("perror");
	pid1 = execute_pid(tree->left, fd, STDOUT_FILENO);
	pid2 = execute_pid(tree->right, fd, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &tree->status, 0);
	waitpid(pid2, &tree->status, 0);
	if (WIFEXITED(tree->status))
		tree->status = WEXITSTATUS(tree->status);
	else if (WIFSIGNALED(tree->status))
	{
		if (WTERMSIG(tree->status) == SIGQUIT)
			ft_fprintf("Quit (core dumped)\n");
		tree->status = 128 + WTERMSIG(tree->status);
	}
	else
		tree->status = 1;
}
