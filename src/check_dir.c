/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 05:04:22 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/08 05:13:02 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_dir(t_btree *tree, char *path)
{
	DIR	*dir;

	if (path && path[ft_strlen(path) - 1] == '/')
	{
		dir = opendir(path);
		if (dir)
		{
			write(2, path, ft_strlen(path));
			write(2, "/: ", 3);
			write(2, "is a directory\n", 15);
			tree->status = 126;
			return (1);
		}
	}
	return (0);
}