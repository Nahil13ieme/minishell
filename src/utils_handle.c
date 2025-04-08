/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:22:47 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/08 15:55:11 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Traite un mot (token standard)
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
static char	*handle_word(t_token_stream *ts, int *i)
{
	char	*segment;
	int		start;
	int		len;

	start = *i;
	while (ts->line[*i] && !ft_isspace(ts->line[*i])
		&& ts->line[*i] != '<' && ts->line[*i] != '>'
		&& ts->line[*i] != ';' && ts->line[*i] != '|'
		&& ts->line[*i] != '&' && ts->line[*i] !='\''
		&& ts->line[*i] != '\"')
		(*i)++;
	len = *i - start;
	segment = ft_substr(ts->line, start, len);
	if (!segment)
	{
		perror("substr");
		exit(EXIT_FAILURE);
	}
	(*i)--;
	return (segment);
}

static char	*handle_quote(t_token_stream *ts, int *i)
{
	char	*segment;
	char	quote;
	int		start;
	int		len;

	start = *i;
	quote = ts->line[*i];
	(*i)++;
	while (ts->line[*i] && ts->line[*i] != quote)
		(*i)++;
	if (ts->line[*i] == 0)
		return (NULL);
	(*i)++;
	len = *i - start;
	segment = ft_substr(ts->line, start, len);
	if (!segment)
		exit_error("malloc failure");
	(*i)--;
	return (segment);
}

int	ft_while_handle_segment(t_token_stream *ts,
	char *word, int i, char **segment)
{
	char	*tmp;

	while (ts->line[i] && ts->line[i] != ' ')
	{
		if (ts->line[i] == '\'' || ts->line[i] == '\"')
			word = handle_quote(ts, &i);
		else if (ts->line[i] != '<' && ts->line[i] != '>'
			&& ts->line[i] != ';' && ts->line[i] != '|'
			&& ts->line[i] != '&')
			word = handle_word(ts, &i);
		else
			break ;
		if (!word)
			return (-1);
		i++;
		tmp = *segment;
		*segment = ft_strjoin(*segment, word);
		free(word);
		free(tmp);
	}
	return (i);
}
