/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:17:48 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 19:18:03 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*handle_word2(char *line, int *i)
{
	char	*segment;
	int		start;
	int		len;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i])
		&& line[*i] != '<' && line[*i] != '>'
		&& line[*i] != ';' && line[*i] != '|'
		&& !(line[*i] == '&' && line[(*i) + 1] == '&')
		&& line[*i] != '\''
		&& line[*i] != '\"' && line[*i] != '$')
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

char	*retrieve_var_word(char *line)
{
	char	*segment;
	char	*tmp;
	char	*word;
	int		i;

	i = 0;
	segment = NULL;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '$')
			word = handle_env_variable(line, &i);
		else if (line[i] == '\'' || line[i] == '"')
			word = handle_quoted_string(line, &i);
		else
			word = handle_word2(line, &i);
		if (!word)
			return (NULL);
		i++;
		tmp = segment;
		segment = ft_strjoin(segment, word);
		free(word);
		free(tmp);
	}
	return (segment);
}

/**
 * @brief Prépare et exécute une commande
 * @param tree Structure arborescente contenant les informations de commande
 */
static void	prepare_and_execute_cmd(t_btree *tree)
{
	if (!tree->cmd || !tree->cmd[0])
		return ;
	if (ft_strcmp(tree->cmd[0], "$?") == 0)
	{
		free(tree->cmd[0]);
		tree->cmd[0] = ft_itoa(get_exit_code());
	}
	tree->cmd = retrieve_var(tree->cmd);
	if (!tree->cmd || !tree->cmd[0])
		return ;
	if (tree->cmd[0][0] == 0)
	{
		tree->status = 0;
		return ;
	}
	execute_path(tree);
}

/**
 * @brief Gère les redirections
 * @param tree Structure arborescente contenant les informations de redirection
 */
static void	handle_redirection(t_btree *tree)
{
	char	*tmp;

	if (!tree->file)
		return ;
	tmp = tree->file;
	tree->file = retrieve_var_word(tree->file);
	free(tmp);
	execute_redirection(tree);
}

/**
 * @brief Exécute récursivement un arbre d'analyse syntaxique
 * @param tree Structure arborescente à exécuter
 */
void	execute_tree(t_btree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->cmd && tree->cmd[0])
		prepare_and_execute_cmd(tree);
	ft_if_execute_andor(tree);
	if (tree->type == NODE_SEMICOLON)
	{
		execute_tree(tree->left);
		execute_tree(tree->right);
		tree->status = tree->right->status;
	}
	if (tree->type == NODE_PIPE)
		execute_pipeline(tree);
	if (tree->type == NODE_REDIR_IN || tree->type == NODE_REDIR_OUT
		|| tree->type == NODE_APPEND || tree->type == NODE_HEREDOC)
		handle_redirection(tree);
	set_exit_code(tree->status);
}
