/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:37:37 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 08:54:43 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Il faut que je fasse en sorte d'appeler les heredocs avant tous les autres 
 * noeuds de l'arbre
 * Stocker le contenu des heredocs dans tree->heredoc.
 * Une fois tous les heredocs traites, continuer l'execution de l'arbre 
 * normalement sans reexecuter l'extraction des donnees, donc juste rediriger
 * l'entree
 */

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	set_exit_code(130);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = heredoc_sigint;
	sigaction(SIGINT, &sa, NULL);
}

char	**extract_content_heredoc(char *delimiter)
{
	char	**cmd;
	char	*line;
	int		i;

	set_heredoc_signals();
	cmd = malloc(sizeof(char *) * 1);
	if (!cmd)
		exit_error("malloc");
	cmd[0] = NULL;
	line = NULL;
	i = 0;
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			break ;
		if (!line || strcmp(line, delimiter) == 0)
			break ;
		cmd[i++] = ft_strdup(line);
		cmd = ft_realloc(cmd, sizeof(char *) * (i + 1), sizeof(char *) * i);
		cmd[i] = NULL;
		free(line);
	}
	return (free(line), cmd);
}

void	apply_heredoc(t_btree *tree, int child)
{
	int		pipe_fds[2];
	int		i;

	if (tree->heredoc == NULL)
		tree->heredoc = extract_content_heredoc(tree->delimiter);
	if (!child)
	{
		if (!tree->heredoc)
			return ;
		if (pipe(pipe_fds) == -1)
			exit_error("pipe");
		i = 0;
		while (tree->heredoc[i])
		{
			write(pipe_fds[1], tree->heredoc[i], ft_strlen(tree->heredoc[i]));
			write(pipe_fds[1], "\n", 1);
			i++;
		}
		close(pipe_fds[1]);
		if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
			exit_error("dup2");
		close(pipe_fds[0]);
	}
}

void	execute_heredoc(t_btree *tree)
{
	t_btree	*nodes[100];
	int		count;
	t_btree	*cmd_node;
	int		saved_stdin;

	cmd_node = tree;
	count = 0;
	while (cmd_node && (cmd_node->type == NODE_HEREDOC
			|| cmd_node->type == NODE_REDIR_IN))
	{
		nodes[count++] = cmd_node;
		cmd_node = cmd_node->left;
	}
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		exit_error("dup");
	while (--count >= 0)
		if (nodes[count]->type == NODE_HEREDOC)
			apply_heredoc(nodes[count], count);
	if (cmd_node)
		execute_tree(cmd_node);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		exit_error("dup2");
	close(saved_stdin);
}
