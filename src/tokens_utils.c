/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:26:49 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 07:38:17 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_control(t_token_type type)
{
	return (type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_PIPE);
}

static int	is_redir(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND);
}

static int	validate_token_list(t_token_stream *ts)
{
	int	i;
	int	ret;

	i = 0;
	while (i < ts->size)
	{
		ret = is_control(ts->tokens[i]->type) || is_redir(ts->tokens[i]->type);
		if (ret)
		{
			if (i == ts->size - 1)
				return (ft_putstr_fd(ERR_NL, 2), 0);
			if (is_control(ts->tokens[i + 1]->type))
				return (ft_putstr_fd(ERR_REDIR, 2), 0);
		}
		i++;
	}
	return (1);
}

int	validate_token_sequence(t_token_stream *ts)
{
	if (ts->size == 0)
		return (0);
	if (ts->tokens[0]->type != TOKEN_WORD && !is_redir(ts->tokens[0]->type))
	{
		ft_fprintf("minishell: syntax error near unexpected token `%s'\n",
			ts->tokens[0]->value);
		return (0);
	}
	if (!validate_token_list(ts))
		return (0);
	if (is_control(ts->tokens[ts->size - 1]->type))
	{
		ft_fprintf(ERR_NL);
		return (0);
	}
	return (1);
}
