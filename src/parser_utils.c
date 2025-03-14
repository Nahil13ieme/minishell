/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:17:14 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/14 18:14:58 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_segment(char *line, int *i)
{
	char	*seg;
	int		start;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
		&& line[*i] != '\'' && line[*i] != '"' && line[*i] != '|' && line[*i] != '$')
		(*i)++;
	seg = ft_substr(line, start, (*i) - start);
	if (!seg)
		return (NULL);
	return (seg);
}

static char	*double_quote_segment(char *temp, char **env)
{
	char	*expanded;
	char	*tmp;
	char	*ret;
	int		start;

	ret = ft_strdup("");
	start = 0;
	while (temp[start])
	{
		if (temp[start] == '$')
		{
			expanded = expand_variable(temp + start, &start, env);
			if (!expanded)
				return (NULL);
		}
		else
			expanded = ft_substr(temp, start++, 1);
		tmp = ret;
		ret = ft_strjoin(ret, expanded);
		free(tmp);
		free(expanded);
	}
	return (ret);
}

char	*handle_double_quote(char *line, int *i, char **env)
{
	char	*temp;
	char	*segment;

	segment = extract_quote(line, i, '"');
	if (!segment)
		return (NULL);
	temp = segment;
	segment = double_quote_segment(temp, env);
	free(temp);
	return (segment);
}

char	*extract_quote(char *line, int *i, char quote)
{
	int		start;
	char	*ret;
	int		len;

	start = *i + 1;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
	{
		len = *i - start;
		ret = ft_substr(line, start, len);
		(*i)++;
		return (ret);
	}
	return (NULL);
}

char	*expand_variable(char *line, int *i, char **env)
{
	char	*var_name;
	char	*var_value;
	int		end;
		
	end = 1;
	while (line[end] && (ft_isalnum(line[end]) || line[end] == '_'))
		end++;
	var_name = ft_substr(line, 1, end - 1);
	if (!var_name)
		return (NULL);
	*i += end;
	if (end == 1)
		return (ft_strdup("$"));
	var_value = get_my_env(env, var_name);
	free(var_name);
	if (!var_value)
	{
		return (ft_strdup(""));
	}
	return (ft_strdup(var_value));
}
