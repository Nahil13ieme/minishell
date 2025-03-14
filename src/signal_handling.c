/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:17:11 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/14 16:23:29 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

/*
 * signal_handler - Handles the signals sent to the shell.
 * @param sig: The signal number.
 *
 * This function handles the signals sent to the shell. It handles SIGINT and
 * SIGQUIT signals. If SIGINT is received, it writes a newline character to the
 * standard output. If SIGQUIT is received, it writes "Quit (core dumped)" to
 * the standard output.
 */
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (g_signal == 0)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
	else
		write(STDOUT_FILENO, "\n", 1);
}
/**
 * Sets up the signal handlers for the parent process.
 */
void	setup_parent_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
/**
 * Sets up the signal handlers for the child process.
 */
void	setup_child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
