/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:22:47 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 18:03:47 by nbenhami         ###   ########.fr       */
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
		tmp = segment;
		segment = ft_strjoin(segment, word);
		free(word);
		free(tmp);
	}
	return (i);
}
