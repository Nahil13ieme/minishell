/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:29:22 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/03 15:28:53 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*handle_double_quote(char *line, int *i, char **env)
{
	char	*segment;
	char	*tmp;
	char	*var_value;

	(*i)++;
	segment = ft_strdup("");
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$')
		{
			tmp = segment;
			var_value = handle_env_variable(line, i, env);
			segment = ft_strjoin(segment, var_value);
			free(var_value);
			free(tmp);
		}
		else
			double_quote_segment(&segment, line, i);
		(*i)++;
	}
	if (line[*i] == '"')
		(*i)++;
	(*i)--;
	return (segment);
}

/**
 * Traite une chaîne de caractères entre guillemets
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
char	*handle_quoted_string(char *line, int *i, char **env)
{
	if (line[*i] == '\'')
		return (handle_simple_quote(line, i));
	else
		return (handle_double_quote(line, i, env));
}

/**
 * Traite un mot (token standard)
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
static char	*handle_word(char *line, int *i)
{
	char	*segment;
	int		start;
	int		len;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i])
		&& line[*i] != '<' && line[*i] != '>'
		&& line[*i] != ';' && line[*i] != '|'
		&& line[*i] != '&' && line[*i] != '\''
		&& line[*i] != '"')
		(*i)++;
	len = *i - start;
	segment = ft_substr(line, start, len);
	if (!segment)
	{
		perror("substr");
		exit(EXIT_FAILURE);
	}
	(*i)--;
	return (segment);
}

int	handle_segment(t_token_stream *ts, char *line, int i, char **env)
{
	char	*segment;
	char	*word;

	segment = NULL;
	while (line[i] && ft_isspace(line[i]))
		i++;
	i = ft_while_handle_segment(line, env, word, i, &segment);
	add_token(ts, create_token(TOKEN_WORD, segment));
	return (free(segment), i);
}
