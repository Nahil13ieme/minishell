/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:27:15 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/25 09:35:33 by nbenhami         ###   ########.fr       */
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
 * Traite une variable d'environnement delimiter par un $
 * @param ts    Le stream de tokens
 * @param line  La ligne d'entrée
 * @param env   Les variables d'environnement
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
static int	handle_env_variable(t_token_stream *ts,
	char *line, int i, char **env)
{
	int		start;
	char	*var_name;
	char	*var_value;

	(void)env;
	start = i + 1;
	i++;
	while (line[i] && (ft_isalpha(line[i]) || line[i] == '_'))
		i++;
	var_name = ft_substr(line, start, i - start);
	var_value = getenv(var_name);
	free(var_name);
	if (!var_value)
		var_value = "";
	add_token(ts, create_token(TOKEN_WORD, var_value));
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
int	process_char(t_token_stream *ts, char *line, int i, char **env)
{
	int	new_i;

	new_i = handle_double_tokens(ts, line, i);
	if (new_i != i)
		return (new_i);
	new_i = handle_single_tokens(ts, line, i);
	if (new_i != i)
		return (new_i);
	if (line[i] == '\'' || line[i] == '"')
		return (handle_quoted_string(ts, line, i, env));
	if (line[i] == '$' && line[i + 1] == '?')
		printf("%d\n", get_exit_code());
	if (line[i] == '$')
		return (handle_env_variable(ts, line, i, env));
	return (handle_word(ts, line, i));
}
