/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:26:49 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/17 14:20:07 by nbenhami         ###   ########.fr       */
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

	i = 0;
	while (i < ts->size - 1)
	{
		if (is_control(ts->tokens[i]->type)
			&& is_control(ts->tokens[i + 1]->type))
		{
			printf("minishell: syntax error near unexpected token `%s'\n",
				ts->tokens[i + 1]->value);
			return (0);
		}
		if (is_redir(ts->tokens[i]->type))
		{
			if (i == ts->size - 1)
				return (ft_putstr_fd(ERR_NL, 2), 0);
			if (is_control(ts->tokens[i + 1]->type)
				|| is_redir(ts->tokens[i + 1]->type))
				return (ft_putstr_fd(ERR_REDIR, 2), 0);
		}
		i++;
	}
	return (1);
}

int	validate_token_sequence(t_token_stream *ts)
{
	if (ts->size == 0)
	{
		ft_putstr_fd("Error: Empty token stream\n", 2);
		return (0);
	}
	if (is_control(ts->tokens[0]->type))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			ts->tokens[0]->value);
		return (0);
	}
	if (!validate_token_list(ts))
		return (0);
	if (is_control(ts->tokens[ts->size - 1]->type))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}
