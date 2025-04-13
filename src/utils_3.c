/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:05:46 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/13 21:17:46 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_error(char *msg)
{
	perror(msg);
	free_glob();
	set_root(NULL, 'f');
	exit(EXIT_FAILURE);
}

int	get_oflags(int type)
{
	if (type == NODE_REDIR_IN)
		return (O_RDONLY);
	else if (type == NODE_REDIR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (type == NODE_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (-1);
}

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
			ft_fprintf("\n\n\nErreur: tab[%d] est NULL\n\n\n", i);
			return (i);
		}
		i++;
	}
	return (i);
}

void	ft_if_modify_export(char *equal_pos, char *var, char **envi,
	char **export)
{
	int	i;

	i = -1;
	if (equal_pos)
	{
		while (envi[++i])
			if (ft_strncmp(envi[i], var, equal_pos - var) == 0)
				return (free(envi[i]));
	}
	else
	{
		while (export[++i])
			if (ft_strncmp(export[i], var, ft_strlen(export[i])) == 0)
				return (free(export[i]));
	}
}

char	**retrieve_var(char **cmd)
{
	char	*segment;
	char	*line;
	char	**ret;
	int		i;
	int		len;

	i = 0;
	len = 0;
	ret = NULL;
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		line = cmd[i];
		segment = retrieve_var_word(line);
		free(line);
		if (segment && segment[0] != 0)
		{
			ret = ft_tab_realloc(ret, sizeof(char *) * (len + 1));
			ret[len] = ft_strdup(segment);
			ret[len + 1] = NULL;
			len++;
		}
		free(segment);
		i++;
	}
	free(cmd);
	return (ret);
}
