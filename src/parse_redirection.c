/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 06:57:05 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 16:47:30 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd_type	get_redirection_type(t_token_stream *ts)
{
	t_cmd_type	type;

	if (current_token_is(ts, TOKEN_REDIR_IN))
		type = NODE_REDIR_IN;
	else if (current_token_is(ts, TOKEN_REDIR_OUT))
		type = NODE_REDIR_OUT;
	else if (current_token_is(ts, TOKEN_APPEND))
		type = NODE_APPEND;
	else
		type = NODE_HEREDOC;
	return (type);
}

static t_btree	*handle_redirection(t_token_stream *ts, t_cmd_type type,
	t_btree *node, int arg_count)
{
	t_btree	*cmd_node;
	char	*redir_file;

	if (!current_token_is(ts, TOKEN_WORD))
		return (NULL);
	redir_file = ts->tokens[ts->current]->value;
	consume_token(ts);
	node = create_node(type, node, NULL, NULL);
	node->file = strdup(redir_file);
	cmd_node = node->left;
	while (cmd_node && cmd_node->type != NODE_COMMAND)
		cmd_node = cmd_node->left;
	if (cmd_node && cmd_node->cmd && current_token_is(ts, TOKEN_WORD))
	{
		while (cmd_node->cmd[0] != NULL && cmd_node->cmd[arg_count])
			arg_count++;
		while (current_token_is(ts, TOKEN_WORD))
		{
			cmd_node->cmd = ft_tab_realloc(cmd_node->cmd, arg_count + 2);
			cmd_node->cmd[arg_count++] = strdup(ts->tokens[ts->current]->value);
			cmd_node->cmd[arg_count] = NULL;
			consume_token(ts);
		}
	}
	return (node);
}

static int	current_token_is_redirection(t_token_stream *ts)
{
	return (current_token_is(ts, TOKEN_REDIR_IN)
		|| current_token_is(ts, TOKEN_REDIR_OUT)
		|| current_token_is(ts, TOKEN_APPEND)
		|| current_token_is(ts, TOKEN_HEREDOC));
}

t_btree	*parse_redirection(t_token_stream *ts, t_btree	*node,
		t_cmd_type	type)
{
	if (!node && current_token_is_redirection(ts))
	{
		node = create_node(NODE_COMMAND, NULL, NULL, NULL);
		node->cmd = malloc(sizeof(char *));
		if (!node->cmd)
			exit_error("malloc");
		node->cmd[0] = NULL;
	}
	else if (!node)
		return (NULL);
	while (current_token_is_redirection(ts))
	{
		type = get_redirection_type(ts);
		consume_token(ts);
		node = handle_redirection(ts, type, node, 0);
		if (!node)
			return (NULL);
		if (type == NODE_HEREDOC)
		{
			node->delimiter = ft_strdup(node->file);
			free(node->file);
			node->file = NULL;
		}
	}
	return (node);
}
