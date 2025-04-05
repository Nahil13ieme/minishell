/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:34:30 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/05 13:52:50 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**sim_glob(char **tab, char c)
{;
	static char	**env = NULL;

	if (c == 'g')
		return (env);
	else if (c == 's')
		env = tab;
	else if (c == 'f')
		free_tab(env);
	return (NULL);
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

void	add_export(char **tab, char *str)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	new_tab = ft_tab_realloc(tab, 1);
	new_tab[i + 1] = ft_strdup(str);
	sim_glob(new_tab, 's');
	set_export();
}

void	ft_while_print_export(char **tab, int i, int j)
{
	int	pass;

	pass = 0;
	if (tab[i][0] == '_' && tab[i][1] == '=')
		return ;
	printf("define -x ");
	while (tab[i][j])
	{
		if (tab[i][j] == '=' && pass == 0)
		{
			printf("=");
			pass = 1;
			printf("\"");
		}
		else if (tab[i][j + 1] == '\0' && pass == 1)
		{
			printf("%c", tab[i][j]);
			printf("\"");
		}
		else
			printf("%c", tab[i][j]);
		j++;
	}
	printf("\n");
}

int	ft_while_set_export(void)
{
	char	*cwd;
	int i;
	char **export;
	
	export = sim_glob(NULL, 'g');
	i = 0;
	while (export[i])
	{
		cwd = getenv("PWD");
		if (ft_strncmp(export[i], "PWD=", 4) == 0)
		{
			free(export[i]);
			export[i] = ft_strjoin("PWD=", cwd);
			sim_glob(export, 'S');
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
