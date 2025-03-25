/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:29:22 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/25 09:35:22 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_simple_quote(t_token_stream *ts, char *line, int i)
{
	char	*segment;
	int		start;
	int		len;

	i++;
	start = i;
	while (line[i] && line[i] != '\'')
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
	if (line[i] == '\'')
		i++;
	return (i);
}

static char	*get_variable_value(char *line, int *i)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i + 1;
	(*i)++;
	while (line[*i] && (ft_isalpha(line[*i]) || line[*i] == '_'))
		(*i)++;
	var_name = ft_substr(line, start, (*i) - start);
	(*i)--;
	var_value = getenv(var_name);
	free(var_name);
	if (!var_value)
		var_value = "";
	return (var_value);
}

static void	double_quote_segment(char **segment, char *line, int i)
{
	char	*tmp;

	tmp = *segment;
	*segment = ft_strjoin(*segment, (char []){line[i], '\0'});
	free(tmp);
	if (!*segment)
	{
		perror("strjoin");
		exit(EXIT_FAILURE);
	}
}

static int	handle_double_quote(t_token_stream *ts,
	char *line, int i, char **env)
{
	char	*segment;

	(void)env;
	i++;
	segment = ft_strdup("");
	while (line[i] && line[i] != '"')
	{
		if (line[i] == '$')
			segment = ft_strjoin(segment, get_variable_value(line, &i));
		else
			double_quote_segment(&segment, line, i);
		i++;
	}
	add_token(ts, create_token(TOKEN_WORD, segment));
	if (line[i] == '"')
		i++;
	return (free(segment), i);
}

/**
 * Traite une chaîne de caractères entre guillemets
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
int	handle_quoted_string(t_token_stream *ts,
	char *line, int i, char **env)
{
	if (line[i] == '\'')
		i = handle_simple_quote(ts, line, i);
	else
		i = handle_double_quote(ts, line, i, env);
	return (i);
}
