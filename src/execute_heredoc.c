/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:37:37 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/07 17:07:36 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char **extract_content(char *delimiter)
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
		if (!line || strcmp(line, delimiter) == 0)
			break;
		cmd[i] = ft_strdup(line);
		if (!cmd[i])
			exit_error("malloc");
		i++;
		cmd = ft_realloc(cmd, sizeof(char *) * (i + 1), sizeof(char *) * i);
		cmd[i] = NULL;
		free(line);
	}
	return (free(line), cmd);
}

static void	apply_heredoc(t_btree *tree, int child)
{
	char	**content;
	int		pipe_fds[2];
	int		i;
	
	content = extract_content(tree->right->cmd[0]);
	if (!child)
	{
		if (!content)
			return;
		if (pipe(pipe_fds) == -1)
			exit_error("pipe");
		i = 0;
		while (content[i])
		{
			write(pipe_fds[1], content[i], ft_strlen(content[i]));
			write(pipe_fds[1], "\n", 1);
			i++;
		}
		close(pipe_fds[1]);
		if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
			exit_error("dup2");
		close(pipe_fds[0]);
	}
	free_tab(content);
}

void execute_heredoc(t_btree *tree, char **envp)
{
	t_btree	*nodes[100];
	int		count;
	t_btree	*cmd_node;
	int		saved_stdin;
	
	cmd_node = tree;
	count = 0;
	while (cmd_node && cmd_node->type == NODE_HEREDOC)
	{
		nodes[count++] = cmd_node;
		cmd_node = cmd_node->left;
	}
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		exit_error("dup");
	while (--count >= 0)
		apply_heredoc(nodes[count], count);
	if (cmd_node)
		execute_tree(cmd_node, envp);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdin);
}

