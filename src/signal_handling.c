/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:17:11 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/09 23:43:43 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (g_signal == 0)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
	}
	else
	{
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	setup_parent_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
