/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:40:35 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/29 17:44:23 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**create_args(t_token_stream *tokens)
{
	char	**args;
	size_t	arg_count;
	t_token	*current;

	args = malloc(sizeof(char *) * 10);
	if (!args)
	{
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
		}
		else
			break ;
	}
	args[arg_count] = NULL;
	return (args);
}

t_btree	*parse_command(t_token_stream *tokens)
{
	t_btree	*node;

	if (!tokens || tokens->current == -1 || tokens->current >= tokens->capacity
		|| tokens->tokens[tokens->current]->type != TOKEN_WORD)
		return (NULL);
	node = create_node(NODE_COMMAND, NULL, NULL, NULL);



	node->cmd = create_args(tokens);
	return (node);
}

void	consume_token(t_token_stream *tokens)
{
	tokens->current++;
	if (tokens->current >= tokens->size)
		tokens->current = -1;
}

int	current_token_is(t_token_stream *tokens, t_token_type type)
{
	if (tokens->current >= tokens->size)
		return (0);
	return (tokens->current < tokens->capacity
		&& tokens->tokens[tokens->current]->type == type);
}
