/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:17:41 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/10 15:13:45 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		if (tab[i] != NULL)
			free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_print_env(char **tab, int export)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (export == 0)
	{
		free_tab(tab);
		tab = sim_glob(NULL, 'g');
	}
	while (tab[i])
	{
		j = 0;
		if (export == 0)
			if (ft_strchr(tab[i], '=') != NULL)
				printf("%s\n", tab[i]);
		if (export == 1)
		{
			ft_while_print_export(tab, i, j);
		}
		i++;
	}
	if (tab != NULL)
		free_tab(tab);
}

/**
 * @brief Fait une copie d un tableaux et le retoune malloc
 * @param tab Tableaux a copier
 * @return Tableaux copier malloc
*/
char	**tab_cpy(char **tab)
{
	char	**cpy;
	int		i;

	i = ft_tablen(tab);
	cpy = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tab[i])
	{
		cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void	ft_old_pwd_replace(char *var)
{
	char	**env;
	int		i;

	i = 0;
	env = sim_glob(NULL, 'g');
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", var);
			if (var != NULL)
				free(var);
			sim_glob(env, 's');
		}
		i++;
	}
}

int	sim_quotes(int nbr, char c)
{
	static int	simple_quote = 0;
	static int	double_quote = 0;

	if (c == 's')
		simple_quote = nbr;
	else if (c == 'S')
		double_quote = nbr;
	else if (c == 'g')
		return (simple_quote);
	else if (c == 'G')
		return (double_quote);
	return (0);
}
