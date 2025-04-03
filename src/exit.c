/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:54:41 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/03 13:31:41 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_exit_code(int code)
{
	sim_exit(code, 's');
}

int	get_exit_code(void)
{
	return (sim_exit(0, 'g'));
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
