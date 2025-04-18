/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:54:41 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 18:56:06 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_exit_code(int code)
{
	sim_exit(code, 's');
}

int	get_exit_code(void)
{
	int	code;

	code = sim_exit(0, 'g');
	return (code);
}

int	sim_exit(int code, char c)
{
	static int	global = 0;

	if (c == 'g')
		return (global);
	else
		global = code;
	return (0);
}
