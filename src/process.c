/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:26:03 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/10 14:42:32 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	apply_all_heredoc(t_btree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		apply_all_heredoc(tree->left);
	if (tree->right && tree->type != NODE_REDIR_IN
		&& tree->type != NODE_REDIR_OUT
		&& tree->type != NODE_APPEND && tree->type != NODE_HEREDOC)
		apply_all_heredoc(tree->right);
	if (tree->type == NODE_HEREDOC)
		apply_heredoc(tree, 1);
}

void	process_line(char *line)
{
	t_token_stream	*ts;

	if (line[0])
	{
		add_history(line);
		ts = tokenize_input(line);
		if (!validate_token_sequence(ts))
		{
			set_exit_code(2);
			free_token_stream(ts);
			return ;
		}
		set_root(parse_input(ts), 's');
		free_token_stream(ts);
		if (set_root(NULL, 'g'))
		{
			apply_all_heredoc(set_root(NULL, 'g'));
			execute_tree(set_root(NULL, 'g'));
			set_exit_code(set_root(NULL, 'g')->status);
			set_root(NULL, 'f');
		}
		else
			ft_fprintf("Error parsing input\n");
	}
}
