/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 05:04:22 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/13 12:23:43 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_dir(t_btree *tree)
{
	DIR	*dir;

	dir = opendir(tree->cmd[0]);
	if (dir)
	{
		write(2, tree->cmd[0], ft_strlen(tree->cmd[0]));
		write(2, ": ", 3);
		write(2, "is a directory\n", 15);
		tree->status = 126;
		return (1);
	}
	return (0);
}

int	check_dir_file(char *file)
{
	DIR	*dir;

	dir = opendir(file);
	if (dir)
	{
		ft_fprintf("minishell: %s: is a directory\n", file);
		return (1);
	}
	return (0);
}
