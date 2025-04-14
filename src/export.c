/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:46:34 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 08:56:12 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Commande built-in pour exporter une variable dans ENV.
 * @param var Variable a exporter.
 */
int	ft_export(char *var, int i)
{
	char	*equal_pos ;
	char	**new_envp;
	char	**envi;

	envi = sim_glob(NULL, 'g');
	if (!var)
		return (print_sort_export(), 0);
	equal_pos = ft_strchr(var, '=');
	if (var[0] == '=' || ft_isdigit(var[0]) || var[0] < 48
		|| (var[0] > 57 && var[0] <= 63))
		return (ft_fprintf("minishell: export: %s not a valid identifier\n",
				var), 1);
	i = ft_if_export(i, var, equal_pos);
	if (i > 0)
	{
		new_envp = ft_tab_realloc(envi, 1);
		new_envp[i] = ft_strdup(var);
		new_envp[i + 1] = NULL;
		sim_glob(new_envp, 's');
		set_export();
	}
	return (0);
}

static int	export_2(char *arg, int *exit)
{
	int		j;
	char	*equal_pos ;
	char	**new_envp;
	char	**envi;

	envi = sim_glob(NULL, 'g');
	j = 0;
	equal_pos = ft_strchr(arg, '=');
	if (arg[0] == '=' || ft_isdigit(arg[0]) || arg[0] < 48
		|| (arg[0] > 57 && arg[0] <= 63))
		return (ft_fprintf("minishell: export: %s not a valid identifier\n",
				arg), 1);
	j = ft_if_export(j, arg, equal_pos);
	if (j == -1)
		*exit = 1;
	if (j > 0)
	{
		new_envp = ft_tab_realloc(envi, 1);
		new_envp[j] = ft_strdup(arg);
		new_envp[j + 1] = NULL;
		sim_glob(new_envp, 's');
		set_export();
	}
	return (0);
}

int	ft_export_2(char **args)
{
	int		exit;
	int		i;

	i = 1;
	exit = 0;
	if (!args[i])
		return (print_sort_export(), 0);
	while (args[i])
	{
		if (export_2(args[i], &exit))
			return (1);
		i++;
	}
	if (exit == 0)
		return (0);
	return (1);
}
