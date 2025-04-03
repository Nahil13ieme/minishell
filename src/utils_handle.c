/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:22:47 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 18:15:31 by nbenhami         ###   ########.fr       */
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

int	ft_while_handle_segment(char *line, char **env, char *word, int i, char **segment)
{
	char	*tmp;

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
		if (!word)
		{
			free(*segment);
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		i++;
		tmp = *segment;
		*segment = ft_strjoin(*segment, word);
		free(word);
		free(tmp);
	}
	return (i);
}
