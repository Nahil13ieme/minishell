/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:17:14 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/12 12:24:09 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_segment(char *line, int *i, char *current_token, char **tokens)
{
	char	*seg;
	int		start;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
		&& line[*i] != '\'' && line[*i] != '"' && line[*i] != '|' && line[*i] != '$')
		(*i)++;
	seg = ft_substr(line, start, (*i) - start);
	if (!seg)
	{
		if (current_token)
		free(current_token);
		return (ft_free_split(tokens), NULL);
	}
	return (seg);
}