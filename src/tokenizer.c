/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:27:15 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/16 19:32:05 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Gère les tokens de double caractères (&&, ||, <<, >>)
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
static int	handle_double_tokens(t_token_stream *ts, char *line, int i)
{
	if (line[i] == '&' && line[i + 1] == '&')
	{
		add_token(ts, create_token(TOKEN_AND, "&&"));
		return (i + 2);
	}
	if (line[i] == '|' && line[i + 1] == '|')
	{
		add_token(ts, create_token(TOKEN_OR, "||"));
		return (i + 2);
	}
	if (line[i] == '<' && line[i + 1] == '<')
	{
		add_token(ts, create_token(TOKEN_REDIR_IN, "<<"));
		return (i + 2);
	}
	if (line[i] == '>' && line[i + 1] == '>')
	{
		add_token(ts, create_token(TOKEN_REDIR_OUT, ">>"));
		return (i + 2);
	}
	return (i);
}

/**
 * Gère les tokens de simple caractère (<, >, ;, |)
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
static int	handle_single_tokens(t_token_stream *ts, char *line, int i)
{
	if (line[i] == '<')
	{
		add_token(ts, create_token(TOKEN_REDIR_IN, "<"));
		return (i + 1);
	}
	if (line[i] == '>')
	{
		add_token(ts, create_token(TOKEN_REDIR_OUT, ">"));
		return (i + 1);
	}
	if (line[i] == ';')
	{
		add_token(ts, create_token(TOKEN_SEMICOLON, ";"));
		return (i + 1);
	}
	if (line[i] == '|')
	{
		add_token(ts, create_token(TOKEN_PIPE, "|"));
		return (i + 1);
	}
	return (i);
}

/**
 * Traite une chaîne de caractères entre guillemets
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
static int	handle_quoted_string(t_token_stream *ts, char *line, int i)
{
	char	quote;
	char	*segment;
	int		start;
	int		len;

	quote = line[i];
	i++;
	start = i;
	while (line[i] && line[i] != quote)
		i++;
	len = i - start;
	segment = ft_substr(line, start, len);
	if (!segment)
	{
		perror("substr");
		exit(EXIT_FAILURE);
	}
	add_token(ts, create_token(TOKEN_QUOTED, segment));
	free(segment);
	if (line[i] == quote)
		i++;
	return (i);
}

/**
 * Traite un mot (token standard)
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
static int	handle_word(t_token_stream *ts, char *line, int i)
{
	char	*segment;
	int		start;
	int		len;

	start = i;
	while (line[i] && !ft_isspace(line[i])
		&& line[i] != '<' && line[i] != '>'
		&& line[i] != ';' && line[i] != '|'
		&& line[i] != '&' && line[i] != '\''
		&& line[i] != '"')
		i++;
	len = i - start;
	segment = ft_substr(line, start, len);
	if (!segment)
	{
		perror("substr");
		exit(EXIT_FAILURE);
	}
	add_token(ts, create_token(TOKEN_WORD, segment));
	free(segment);
	return (i);
}

/**
 * Traite un caractère spécifique et décide quelle fonction appeler
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
int	process_char(t_token_stream *ts, char *line, int i)
{
	int	new_i;

	new_i = handle_double_tokens(ts, line, i);
	if (new_i != i)
		return (new_i);
	new_i = handle_single_tokens(ts, line, i);
	if (new_i != i)
		return (new_i);
	if (line[i] == '\'' || line[i] == '"')
		return (handle_quoted_string(ts, line, i));
	return (handle_word(ts, line, i));
}
