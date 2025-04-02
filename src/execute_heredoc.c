/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:37:37 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/03 01:24:24 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/**
 * @todo: Retrieve var value if flag is true
 * @todo: Create a pipe with the cmd and send it to the stdin of tree->left
 * @todo: Close the pipe and its done
 */
void	execute_heredoc(t_btree *tree, char **envp)
{
	char	*line;
	char	**cmd;
	int		i;
	int		env_var;

	i = 0;
	env_var = 0;
	line = NULL;
	cmd = malloc(sizeof(char *) * 1);
	if (!cmd)
		exit_error("malloc");
	cmd[0] = NULL;
	if (tree->right->cmd[0] == '\'' && tree->right->cmd[ft_strlen(tree->right->cmd[0]) - 1] == '\'')
		env_var = 1;
	while (1)
	{
		line = readline("> ");
		if (ft_memcmp(line, tree->right->cmd[0], ft_strlen(tree->right->cmd[0])) == 0)
			break ;
		if (env_var)
		{
			if (ft_strchr(line, '$'))
				line = ft_env_var(line, envp);
			else
				line = ft_strdup(line);
		}
		cmd[i] = ft_strdup(line);
		if (!cmd[i])
			exit_error("malloc");
		i++;
		cmd = ft_realloc(cmd, sizeof(char *) * (i + 1), sizeof(char *) * (i));
		cmd[i] = NULL;
		free(line);
		line = NULL;
	}
	free(line);
	(void)envp;
}