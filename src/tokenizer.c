/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:27:15 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/13 11:50:53 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Gère les tokens de double caractères (&&, ||, <<, >>)
 * @param ts    Le stream de tokens
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
static int	handle_double_tokens(t_token_stream *ts, int i)
{
	if (ts->line[i] == '&' && ts->line[i + 1] == '&')
	{
		add_token(ts, create_token(TOKEN_AND, "&&"));
		return (i + 2);
	}
	if (ts->line[i] == '|' && ts->line[i + 1] == '|')
	{
		add_token(ts, create_token(TOKEN_OR, "||"));
		return (i + 2);
	}
	if (ts->line[i] == '<' && ts->line[i + 1] == '<')
	{
		add_token(ts, create_token(TOKEN_HEREDOC, "<<"));
		return (i + 2);
	}
	if (ts->line[i] == '>' && ts->line[i + 1] == '>')
	{
		add_token(ts, create_token(TOKEN_APPEND, ">>"));
		return (i + 2);
	}
	return (i);
}

/**
 * Gère les tokens de simple caractère (<, >, ;, |)
 * @param ts    Le stream de tokens
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
static int	handle_single_tokens(t_token_stream *ts, int i)
{
	if (ts->line[i] == '<')
	{
		add_token(ts, create_token(TOKEN_REDIR_IN, "<"));
		return (i + 1);
	}
	if (ts->line[i] == '>')
	{
		add_token(ts, create_token(TOKEN_REDIR_OUT, ">"));
		return (i + 1);
	}
	if (ts->line[i] == ';')
	{
		add_token(ts, create_token(TOKEN_SEMICOLON, ";"));
		return (i + 1);
	}
	if (ts->line[i] == '|')
	{
		add_token(ts, create_token(TOKEN_PIPE, "|"));
		return (i + 1);
	}
	return (i);
}

/**
 * Traite une variable d'environnement delimiter par un $
 * @param ts    Le stream de tokens
 * @param env   Les variables d'environnement
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
char	*handle_env_variable(char *line, int *i)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *i + 1;
	(*i)++;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	if (line[*i - 1] == '$' && line[*i] == '?')
		return (ft_itoa(get_exit_code()));
	var_name = ft_substr(line, start, *i - start);
	var_value = return_env(var_name);
	free(var_name);
	if (line[*i - 1] == '$')
		var_value = ft_strdup("$");
	else if (!var_value)
		var_value = ft_strdup("");
	(*i)--;
	return (var_value);
}

/**
 * Traite un caractère spécifique et décide quelle fonction appeler
 * @param ts    Le stream de tokens
 * @param i     Index actuel dans la ligne
 * @return      Nouvel index après traitement
 */
int	process_char(t_token_stream *ts, int i)
{
	int	new_i;

	new_i = handle_double_tokens(ts, i);
	if (new_i != i)
		return (new_i);
	new_i = handle_single_tokens(ts, i);
	if (new_i != i)
		return (new_i);
	return (handle_segment(ts, i));
}
