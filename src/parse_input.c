/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:00:09 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/25 09:41:02 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * On doit parser les tokens dans le binarytree.
 * On fait une fonction recursive a l'envers pour
 * avoir les priorites en premier.
 * Ordre du - au + : ; && || | < > << >>
 */

t_btree	*parse_input(t_token_stream *tokens)
{
	return (parse_sequence(tokens));
}

t_btree	*parse_sequence(t_token_stream *tokens)
{
	t_btree	*node;
	t_btree	*right;

	node = parse_logical(tokens);
	if (!node)
		return (NULL);
	while (current_token_is(tokens, TOKEN_SEMICOLON))
	{
		consume_token(tokens);
		right = parse_logical(tokens);
		node = create_node(NODE_SEMICOLON, node, right, NULL);
	}
	return (node);
}

t_btree	*parse_logical(t_token_stream *tokens)
{
	t_btree		*node;
	t_btree		*right;
	t_cmd_type	type;

	node = parse_redirection(tokens);
	if (!node)
		return (NULL);
	while (current_token_is(tokens, TOKEN_AND)
		|| current_token_is(tokens, TOKEN_OR))
	{
		if (current_token_is(tokens, TOKEN_AND))
			type = NODE_AND;
		else
			type = NODE_OR;
		consume_token(tokens);
		right = parse_redirection(tokens);
		node = create_node(type, node, right, NULL);
	}
	return (node);
}

t_btree	*parse_pipeline(t_token_stream *tokens)
{
	t_btree	*node;
	t_btree	*right;

	node = parse_command(tokens);
	if (!node)
		return (NULL);
	while (current_token_is(tokens, TOKEN_PIPE))
	{
		consume_token(tokens);
		right = parse_command(tokens);
		node = create_node(NODE_PIPE, node, right, NULL);
	}
	return (node);
}

t_btree	*parse_redirection(t_token_stream *tokens)
{
	t_btree		*node;
	t_btree		*right;
	t_cmd_type	type;

	node = parse_pipeline(tokens);
	if (!node)
		return (NULL);
	while (current_token_is(tokens, TOKEN_REDIR_IN)
		|| current_token_is(tokens, TOKEN_REDIR_OUT))
	{
		if (current_token_is(tokens, TOKEN_REDIR_IN))
			type = NODE_REDIR_IN;
		else if (current_token_is(tokens, TOKEN_REDIR_OUT))
			type = NODE_REDIR_OUT;
		else if (current_token_is(tokens, TOKEN_APPEND))
			type = NODE_APPEND;
		else if (current_token_is(tokens, TOKEN_HEREDOC))
			type = NODE_HEREDOC;
		else
			break ;
		consume_token(tokens);
		right = parse_pipeline(tokens);
		node = create_node(type, node, right, NULL);
	}
	return (node);
}
