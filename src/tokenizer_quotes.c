/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:29:22 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/08 16:17:25 by nbenhami         ###   ########.fr       */
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
	sim_quotes(1, 's');
	if (line[*i] == 0)
		return (free(segment), NULL);
	return (segment);
}

static void	double_quote_segment(char *line, char **segment, int *i)
{
	char	*tmp;

	tmp = *segment;
	*segment = ft_strjoin(*segment, (char []){line[*i], '\0'});
	free(tmp);
	if (!*segment)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

static char	*handle_double_quote(char *line, int *i)
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
			var_value = handle_env_variable(line, i);
			segment = ft_strjoin(segment, var_value);
			free(var_value);
			free(tmp);
		}
		else
			double_quote_segment(line, &segment, i);
		(*i)++;
	}
	if (line[*i] == 0)
		return (free(segment), NULL);
	return (segment);
}

/**
 * Traite une chaîne de caractères entre guillemets
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
char	*handle_quoted_string(char *line, int *i)
{
	if (line[*i] == '\'')
		return (handle_simple_quote(line, i));
	else
		return (handle_double_quote(line, i));
}

int	handle_segment(t_token_stream *ts, int i)
{
	char	*segment;
	char	*word;

	word = NULL;
	segment = NULL;
	while (ts->line[i] && ft_isspace(ts->line[i]))
		i++;
	i = ft_while_handle_segment(ts, word, i, &segment);
	if (i == -1)
	{
		free(segment);
		write(2, "Error: unclosed quotes\n", 24);
		return (-1);
	}
	if (!segment)
	{
		printf("Couldnt resolve line : %c\n", ts->line[i]);
		return (-1);
	}
	add_token(ts, create_token(TOKEN_WORD, segment));
	return (free(segment), i);
}
