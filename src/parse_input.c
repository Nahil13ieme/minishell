/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:00:09 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/27 14:39:40 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * On doit parser les tokens dans le binarytree.
 * On fait une fonction recursive a l'envers pour
 * avoir les priorites en premier.
 * Ordre du - au + : ; && || | < > << >>
 */

t_btree	*parse_input(t_token_stream *ts)
{
	return (parse_sequence(ts));
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

t_btree	*parse_redirection(t_token_stream *ts)
{
	t_btree		*node;
	t_btree		*right;
	t_cmd_type	type;

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
		else if (current_token_is(ts, TOKEN_HEREDOC))
			type = NODE_HEREDOC;
		consume_token(ts);
		right = parse_command(ts);
		node = create_node(type, node, right, NULL);
	}
	return (node);
}
