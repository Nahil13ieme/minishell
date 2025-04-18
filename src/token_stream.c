/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:18:24 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/08 11:25:12 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Ajoute un token au stream de tokens
 * @param stream Le stream de tokens
 * @param token  Le token à ajouter.
 * 
 * Exit si realloc echoue.
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
 * @brief Creer un token
 * * @param type  Le type du token
 * * @param value La valeur du token
 * * @return Un pointeur vers le token.
 * * 		 Exit si malloc echoue.
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
 * @brief Creer un stream de tokens
 * * @return Un pointeur vers le stream de tokens.
 * * 		 Exit si malloc echoue.
 */
t_token_stream	*create_token_stream(char *line)
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
	ts->line = line;
	if (!ts->tokens)
	{
		perror("malloc");
		free(ts);
		exit(EXIT_FAILURE);
	}
	return (ts);
}

void	free_token_stream(t_token_stream *ts)
{
	int	i;

	i = 0;
	while (i < ts->size)
	{
		free(ts->tokens[i]->value);
		free(ts->tokens[i]);
		i++;
	}
	free(ts->tokens);
	free(ts);
	ts = NULL;
}

/**
 * * @brief Processes the input line character by character.
 * * @param line The input line to process.
 * * @param env  The environment variables.
 * * @return a pointer to the token stream.
 */
t_token_stream	*tokenize_input(char *line)
{
	t_token_stream	*ts;
	int				i;

	ts = create_token_stream(line);
	i = 0;
	while (ts->line[i])
	{
		while (ts->line[i] && ft_isspace(ts->line[i]))
			i++;
		if (ts->line[i] == '\0')
			break ;
		i = process_char(ts, i);
		if (i == -1)
		{
			free_token_stream(ts);
			ts = create_token_stream(line);
			return (ts);
		}
	}
	return (ts);
}
