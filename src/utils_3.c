/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:26:05 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/09 12:27:45 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
	{
		if (!tab[i])
		{
			printf("\n\n\nErreur: tab[%d] est NULL\n\n\n", i);
			return (i);
		}
		i++;
	}
	return (i);
}

char	**ft_tab_realloc(char **tab, size_t new_size)
{
	size_t	old_size;
	char	**new_tab;
	size_t	i;

	old_size = 0;
	i = 0;
	old_size = ft_tablen(tab);
	new_tab = malloc(sizeof(char *) * (old_size + new_size + 1));
	if (!new_tab)
		return (NULL);
	while (i < old_size)
	{
		new_tab[i] = tab[i];
		i++;
	}
	while (i < old_size + new_size)
	{
		new_tab[i] = NULL;
		i++;
	}
	new_tab[i] = NULL;
	free(tab);
	return (new_tab);
}

void	open_fd(int count, t_btree *nodes[100], int o_flags, int std)
{
	int	i;
	int	fd;

	i = count - 1;
	while (i >= 0)
	{
		fd = open(nodes[i]->file, o_flags, 0644);
		if (fd == -1)
			exit_error("open");
		if (dup2(fd, std) == -1)
			exit_error("dup2");
		close(fd);
		i--;
	}
}
