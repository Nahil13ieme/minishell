/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:37:37 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/03 18:05:20 by nbenhami         ###   ########.fr       */
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
		if (!line || ft_memcmp(line, delimiter, ft_strlen(delimiter)) == 0)
			return (free(line), free_tab(cmd), NULL);
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

void	execute_heredoc(t_btree *tree, char **envp)
{
	char	**cmd;
	int	fd;
	int	saved_stdin;
	
	cmd = extract_content(tree->right->cmd[0]);
	if (!cmd)
		return ;
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		exit_error("dup");
	fd = open(tree->file, O_RDONLY);
	if (fd == -1)
		exit_error("open");
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_error("dup2");
	close(fd);
	execute_tree(tree->left, envp);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdin);
	free(cmd);
}
