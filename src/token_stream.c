/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:18:24 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/16 19:31:34 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Initializes a token stream.
 * * @param stream A pointer to the token stream to initialize.
 * * @param token A pointer to the token to add to the stream.
 * * @return A pointer to the initialized token stream.
 * * 		 Exit if realloc fails.
 */
void	add_token(t_token_stream *stream, t_token *token)
{
	if (stream->size >= stream->capacity)
	{
		stream->capacity *= 2;
		stream->tokens = ft_realloc(stream->tokens,
				stream->capacity * sizeof(t_token *),
				stream->size * sizeof(t_token *));
		if (!stream->tokens)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
	}
	stream->tokens[stream->size++] = token;
}

/**
 * @brief Creates a new token.
 * * @param type The type of the token.
 * * @param value The value of the token.
 * * @return A pointer to the newly created token.
 * * 		 Exit if malloc or strdup fails.
 */
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		perror("strdup");
		free(token);
		exit(EXIT_FAILURE);
	}
	return (token);
}

/**
 * @brief Creates a new token stream.
 * * @return A pointer to the newly created token stream.
 * * 		 Exit if malloc fails.
 */
t_token_stream	*create_token_stream(void)
{
	t_token_stream	*ts;

	ts = malloc(sizeof(t_token_stream));
	if (!ts)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ts->capacity = 10;
	ts->size = 0;
	ts->current = 0;
	ts->tokens = malloc(ts->capacity * sizeof(t_token *));
	if (!ts->tokens)
	{
		perror("malloc");
		free(ts);
		exit(EXIT_FAILURE);
	}
	return (ts);
}

t_token_stream	*tokenize_input(char *line)
{
	t_token_stream	*ts;
	int				i;

	ts = create_token_stream();
	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i] == '\0')
			break ;
		i = process_char(ts, line, i);
	}
	return (ts);
}
