/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:29:22 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/01 18:44:17 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*handle_simple_quote(char *line, int *i)
{
	char	*segment;
	int		start;
	int		len;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	len = *i - start;
	segment = ft_substr(line, start, len);
	if (!segment)
	{
		perror("substr");
		exit(EXIT_FAILURE);
	}
	if (line[*i] == '\'')
		(*i)++;
	(*i)--;
	return (segment);
}

static void	double_quote_segment(char **segment, char *line, int *i)
{
	char	*tmp;

	tmp = *segment;
	*segment = ft_strjoin(*segment, (char []){line[*i], '\0'});
	free(tmp);
	if (!*segment)
	{
		perror("strjoin");
		exit(EXIT_FAILURE);
	}
}

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
	char	*tmp;
	char	*word;

	segment = NULL;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '$')
			word = handle_env_variable(line, &i, env);
		else if (line[i] == '\'' || line[i] == '"')
			word = handle_quoted_string(line, &i, env);
		else if (line[i] != '<' && line[i] != '>'
			&& line[i] != ';' && line[i] != '|'
			&& line[i] != '&')
			word = handle_word(line, &i);
		else
			break ;
		i++;
		tmp = segment;
		segment = ft_strjoin(segment, word);
		free(word);
		free(tmp);
	}
	add_token(ts, create_token(TOKEN_WORD, segment));
	return (free(segment), i);
}
