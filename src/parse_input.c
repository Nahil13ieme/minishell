/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:00:09 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 16:52:31 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_btree	*parse_input(t_token_stream *ts)
{
	t_btree	*root;

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

	node = parse_redirection(ts, parse_command(ts),
			get_redirection_type(ts));
	if (!node)
		return (NULL);
	while (current_token_is(ts, TOKEN_PIPE))
	{
		consume_token(ts);
		right = parse_redirection(ts, parse_command(ts),
				get_redirection_type(ts));
		node = create_node(NODE_PIPE, node, right, NULL);
	}
	return (node);
}
