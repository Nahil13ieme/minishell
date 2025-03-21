/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:00:09 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/21 12:02:56 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * On doit parser les tokens dans le binarytree.
 * On fait une fonction recursive a l'envers pour
 * avoir les priorites en premier.
 * Ordre du - au + : ; && || | < > << >> (peut etre a revoir pour les redirections)
 */

t_btree	*parse_input(t_token_stream *tokens)
{
	return (parse_sequence(tokens));
}

t_btree	*parse_sequence(t_token_stream *tokens)
{
	t_btree	*node;
	t_btree	*right;
	t_btree	*new_node;
	
	node = parse_logical(tokens);
	if (!node)
		return (NULL);
	while (current_token_is(tokens, TOKEN_SEMICOLON))
	{
		consume_token(tokens);
		right = parse_logical(tokens);
		new_node = malloc(sizeof(t_btree));
		if (!new_node)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		new_node = create_node(NODE_SEMICOLON, node, right, NULL);
		node = new_node;
	}
	return (node);
}

t_btree	*parse_logical(t_token_stream *tokens)
{
	t_btree	*node;
	t_btree	*right;
	t_btree	*new_node;
	t_cmd_type	type;
	
	node = parse_redirection(tokens);
	if (!node)
		return (NULL);
	while (current_token_is(tokens, TOKEN_AND)
		|| current_token_is(tokens, TOKEN_OR))
	{
		type = (current_token_is(tokens, TOKEN_AND)) ? NODE_AND : NODE_OR;
		consume_token(tokens);
		right = parse_redirection(tokens);
		new_node = malloc(sizeof(t_btree));
		if (!new_node)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		new_node = create_node(type, node, right, NULL);
		node = new_node;
	}
	return (node);
}

t_btree	*parse_pipeline(t_token_stream *tokens)
{
	t_btree	*node;
	t_btree	*right;
	t_btree	*new_node;
	
	node = parse_command(tokens);
	if (!node)
		return (NULL);
	while (current_token_is(tokens, TOKEN_PIPE))
	{
		consume_token(tokens);
		right = parse_command	(tokens);
		new_node = malloc(sizeof(t_btree));
		if (!new_node)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		new_node = create_node(NODE_PIPE, node, right, NULL);
		node = new_node;
	}
	return (node);
}

t_btree	*parse_redirection(t_token_stream *tokens)
{
	t_btree		*node;
	t_btree		*right;
	t_btree		*new_node;
	t_cmd_type	type;
	
	node = parse_pipeline(tokens);
	if (!node)
		return (NULL);
	while (current_token_is(tokens, TOKEN_REDIR_IN) ||
		current_token_is(tokens, TOKEN_REDIR_OUT))
	{
		type = (current_token_is(tokens, TOKEN_REDIR_IN)) ? NODE_REDIR_IN : NODE_REDIR_OUT;
		consume_token(tokens);
		right = parse_pipeline(tokens);
		new_node = malloc(sizeof(t_btree));
		if (!new_node)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		new_node = create_node(type, node, right, NULL);
		node = new_node;
	}
	return (node);
}

t_btree	*parse_command(t_token_stream *tokens)
{
	t_btree	*node;
	char	**args;
	size_t	arg_count;
	t_token	*current;

	if (!tokens || tokens->current >= tokens->capacity || tokens->tokens[tokens->current]->type != TOKEN_WORD) {
		return (NULL);
	}
	node = malloc(sizeof(t_btree));
	if (!node)
	{
		perror("Erreur d'allocation mémoire pour le nœud");
		exit(EXIT_FAILURE);
	}
	node->type = NODE_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->cmd = NULL;
	node->redir_in = NULL;
	node->redir_out = NULL;
	node->append = NULL;
	node->heredoc = NULL;
	args = malloc(sizeof(char *) * 10);
	if (!args) {
		perror("Erreur d'allocation mémoire pour les arguments");
		exit(EXIT_FAILURE);
	}
	arg_count = 0;
	while (tokens->current < tokens->size)
	{
		current = tokens->tokens[tokens->current];
		if (current->type == TOKEN_WORD)
		{
			args[arg_count++] = strdup(current->value);
			tokens->current++;
		} else
			break;
	}
	args[arg_count] = NULL;
	node->cmd = args;
	return (node);
}

void	consume_token(t_token_stream *tokens)
{
	tokens->current++;
	if (tokens->current >= tokens->size)
		tokens->current = 0;
}

int	current_token_is(t_token_stream *tokens, t_token_type type)
{
	if (tokens->current >= tokens->size)
		return (0);
	return (tokens->current < tokens->capacity
			&& tokens->tokens[tokens->current]->type == type);
}