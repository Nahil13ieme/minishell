/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:26:03 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/15 11:48:23 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	apply_all_heredoc(t_btree *tree)
{
	if (!tree)
		return (0);
	if (tree->left)
		apply_all_heredoc(tree->left);
	if (tree->right && tree->type != NODE_REDIR_IN
		&& tree->type != NODE_REDIR_OUT
		&& tree->type != NODE_APPEND && tree->type != NODE_HEREDOC)
		apply_all_heredoc(tree->right);
	if (g_signal == SIGINT)
		return (1);
	if (tree->type == NODE_HEREDOC)
		apply_heredoc(tree, 1);
	if (g_signal == SIGINT)
		return (1);
	return (0);
}

void	process_line(char *line)
{
	t_token_stream	*ts;

	if (line[0])
	{
		add_history(line);
		ts = tokenize_input(line);
		if (!validate_token_sequence(ts))
			return (set_exit_code(2), free_token_stream(ts));
		set_root(parse_input(ts), 's');
		free_token_stream(ts);
		if (set_root(NULL, 'g'))
		{
			if (!apply_all_heredoc(set_root(NULL, 'g')))
			{
				execute_tree(set_root(NULL, 'g'));
				set_exit_code(set_root(NULL, 'g')->status);
				if (g_signal == SIGINT)
					set_exit_code(130);
			}
			set_root(NULL, 'f');
		}
		else
			return (ft_fprintf("Error parsing input\n"), set_exit_code(1));
	}
}
