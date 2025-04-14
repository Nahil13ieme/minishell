/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:39:30 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/14 16:40:01 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_std(t_btree *node)
{
	int	std;

	if (node->type == NODE_REDIR_IN || node->type == NODE_HEREDOC)
		std = STDIN_FILENO;
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_APPEND)
		std = STDOUT_FILENO;
	else
		std = -1;
	return (std);
}

void	execute_redirection(t_btree *tree)
{
	if (tree->type == NODE_REDIR_OUT || tree->type == NODE_APPEND)
		execute(tree);
	else if (tree->type == NODE_REDIR_IN)
		execute(tree);
	else if (tree->type == NODE_HEREDOC)
		execute_heredoc(tree);
}
