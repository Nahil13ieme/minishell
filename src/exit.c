/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:54:41 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/26 15:41:12 by toto             ###   ########.fr       */
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
	static int global = 0;
	
	if (c == 'g')
		return (global);
	else
		global = code;
	return (0);
}
