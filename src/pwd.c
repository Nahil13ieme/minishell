/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:51:40 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/12 12:09:35 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
    {
        ft_putstr_fd("pwd: ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putchar_fd('\n', 2);
        return ;
    }
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	free(path);
}
