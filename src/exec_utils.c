/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:14:43 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/15 01:37:03 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Initializes a simple command structure.
 * This function allocates memory for a t_cmd structure and initializes its members
 * to default values. If memory allocation fails, it prints an error and returns NULL.
 * @return A pointer to the initialized t_cmd structure, or NULL on failure.
 */
t_cmd	*init_command(void)
{
	t_cmd	*simple_cmd;

	simple_cmd = malloc(sizeof(t_cmd));
	if (!simple_cmd)
	{
		perror("malloc");
		return (NULL);
	}
	simple_cmd->cmd = NULL;
	simple_cmd->argc = 0;
	simple_cmd->avac = 1;
	return (simple_cmd);
}

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (perror("malloc"), NULL);
	exec->scmds = malloc(sizeof(t_cmd *) * 2);
	if (!exec->scmds)
		return (perror("malloc"), free(exec), NULL);
	exec->scmds[0] = init_command();
	if (!exec->scmds[0])
		return (perror("malloc"), free(exec->scmds), free(exec), NULL);
	exec->scmds[1] = NULL;
	exec->avac_sc = 0;
	exec->nbr_cmds = 0;
	exec->bg = 0;
	exec->out = NULL;
	exec->in = NULL;
	exec->err = NULL;
	exec->status = -1;
	return (exec);
}

void free_exec(t_exec *exec)
{
	int i;
	int j;

	if (!exec)
		return ;
	i = 0;
	while (exec->scmds[i])
	{
		if (exec->scmds[i]->cmd)
		{
			j = 0;
			while (exec->scmds[i]->cmd[j])
			{
				free(exec->scmds[i]->cmd[j]);
				j++;
			}
			free(exec->scmds[i]->cmd);
		}
		free(exec->scmds[i]);
		i++;
	}
	free(exec->scmds);
	free(exec);
}
