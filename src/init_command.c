/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:14:43 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/14 16:26:25 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Initializes a simple command structure.
 * This function allocates memory for a t_cmd structure and initializes its members
 * to default values. If memory allocation fails, it prints an error and returns NULL.
 * @return A pointer to the initialized t_cmd structure, or NULL on failure.
 */
t_cmd	*init_simple_command(void)
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
	simple_cmd->avac = 0;
	return (simple_cmd);
}