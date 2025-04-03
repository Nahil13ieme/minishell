/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:37:37 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/03 18:54:19 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @todo: Retrieve var value if flag is true
 * @todo: Create a pipe with the cmd and send it to the stdin of tree->left
 * @todo: Close the pipe and its done
 */

static char	**extract_content(char *delimiter)
{
	char	**cmd;
	char	*line;
	int		i;

	cmd = malloc(sizeof(char *) * 1);
	if (!cmd)
		exit_error("malloc");
	cmd[0] = NULL;
	line = NULL;
	i = 0;
	while (1)
	{
		line = readline("> ");
		if (ft_memcmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		cmd[i] = ft_strdup(line);
		if (!cmd[i])
			exit_error("malloc");
		i++;
		cmd = ft_realloc(cmd, sizeof(char *) * (i + 1), sizeof(char *) * (i));
		cmd[i] = NULL;
		free(line);
		line = NULL;
	}
	return (free(line), cmd);
}

void execute_heredoc(t_btree *tree, char **envp)
{
	char **cmd;
	int pipe_fds[2];
	int saved_stdin;
	int i;
	
	cmd = extract_content(tree->right->cmd[0]);
	if (!cmd)
		return;
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		exit_error("dup");
	if (pipe(pipe_fds) == -1)
		exit_error("pipe");
	i = 0;
	while (cmd[i])
	{
		write(pipe_fds[1], cmd[i], ft_strlen(cmd[i]));
		write(pipe_fds[1], "\n", 1);
		i++;
	}
	close(pipe_fds[1]);
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
		exit_error("dup2");
	close(pipe_fds[0]);
	execute_tree(tree->left, envp);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdin);
	free_tab(cmd);
}
