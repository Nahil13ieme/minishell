/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 01:24:42 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/03 01:25:23 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_signal = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		g_signal = 131;
	}
}