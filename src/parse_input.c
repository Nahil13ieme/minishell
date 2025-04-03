/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:00:09 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/03 18:28:24 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_btree	*parse_input(t_token_stream *ts)
{
	t_btree *root;

	root = parse_sequence(ts);
	return (root);
}

t_btree	*parse_sequence(t_token_stream *ts)
{
	t_btree	*node;
	t_btree	*right;

	node = parse_logical(ts);
	if (!node)
		return (NULL);
	while (current_token_is(ts, TOKEN_SEMICOLON))
	{
		consume_token(ts);
		right = parse_logical(ts);
		if (!right)
			break ;
		node = create_node(NODE_SEMICOLON, node, right, NULL);
	}
	return (node);
}

t_btree	*parse_logical(t_token_stream *ts)
{
	t_btree		*node;
	t_btree		*right;
	t_cmd_type	type;

	node = parse_pipeline(ts);
	if (!node)
		return (NULL);
	while (current_token_is(ts, TOKEN_AND)
		|| current_token_is(ts, TOKEN_OR))
	{
		if (current_token_is(ts, TOKEN_AND))
			type = NODE_AND;
		else
			type = NODE_OR;
		consume_token(ts);
		right = parse_pipeline(ts);
		node = create_node(type, node, right, NULL);
	}
	return (node);
}

t_btree	*parse_pipeline(t_token_stream *ts)
{
	t_btree	*node;
	t_btree	*right;

	node = parse_redirection(ts);
	if (!node)
		return (NULL);
	while (current_token_is(ts, TOKEN_PIPE))
	{
		consume_token(ts);
		right = parse_redirection(ts);
		node = create_node(NODE_PIPE, node, right, NULL);
	}
	return (node);
}

t_btree *parse_redirection(t_token_stream *ts)
{
	t_btree		*node;
	t_btree		*right;
	t_cmd_type	type;
	char		*redir_file;

	node = parse_command(ts);
	if (!node)
		return (NULL);
	while (current_token_is(ts, TOKEN_REDIR_IN)
		|| current_token_is(ts, TOKEN_REDIR_OUT)
		|| current_token_is(ts, TOKEN_APPEND)
		|| current_token_is(ts, TOKEN_HEREDOC))
	{
		if (current_token_is(ts, TOKEN_REDIR_IN))
			type = NODE_REDIR_IN;
		else if (current_token_is(ts, TOKEN_REDIR_OUT))
			type = NODE_REDIR_OUT;
		else if (current_token_is(ts, TOKEN_APPEND))
			type = NODE_APPEND;
		else
			type = NODE_HEREDOC;
		consume_token(ts);
		if (type != NODE_HEREDOC)
		{
			redir_file = ts->tokens[ts->current]->value;
			consume_token(ts);
			node = create_node(type, node, NULL, NULL);
			node->file = strdup(redir_file);
			t_btree *cmd_node = node->left;
			while (cmd_node && cmd_node->type != NODE_COMMAND)
			cmd_node = cmd_node->left;
			if (cmd_node && current_token_is(ts, TOKEN_WORD))
			{
				int arg_count = 0;
				while (cmd_node->cmd[arg_count])
					arg_count++;
				while (current_token_is(ts, TOKEN_WORD))
				{
					cmd_node->cmd = ft_tab_realloc(cmd_node->cmd, arg_count + 2);
					cmd_node->cmd[arg_count++] = strdup(ts->tokens[ts->current]->value);
					cmd_node->cmd[arg_count] = NULL;
					consume_token(ts);
				}
			}
		}
		else
		{
			right = parse_command(ts);
			node = create_node(type, node, right, NULL);
		}
	}
	return (node);
}
