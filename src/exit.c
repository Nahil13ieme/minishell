/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:09:38 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/09 23:43:25 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_exit(char **command)
{
	free(command);
	rl_clear_history();
	printf("Log out\n");
	exit(0);
}
