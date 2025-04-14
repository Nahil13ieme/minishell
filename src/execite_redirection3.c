/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execite_redirection3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:18:15 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 20:18:20 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_std(int std, int *fd_in, int new_fd, int *fd_out)
{
	if (std == STDIN_FILENO)
	{
		if (*fd_in != -1)
			close(*fd_in);
		*fd_in = new_fd;
	}
	else if (std == STDOUT_FILENO)
	{
		if (*fd_out != -1)
			close(*fd_out);
		*fd_out = new_fd;
	}
}