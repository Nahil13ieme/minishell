/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:43:56 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 22:29:04 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_identifier(char *var, int i)
{
	int	before;

	before = 0;
	while (var[i])
	{
		if (var[i] == '=')
			before = 1;
		if ((var[i] < 48 || var[i] > 57) && (var[i] < 65 || var[i] > 90)
			&& (var[i] < 95 || var[i] > 95) && (var[i] < 97 || var[i] > 122)
			&& before == 0)
			return (set_exit_code(1),
				ft_fprintf("minishell: export: %s not a valid identifier\n",
					var),
				-1);
		i++;
	}
	return (1);
}

static int	check_and_replace(char **envi, char *var, int i)
{
	if (search_c(var, '=') == 0 && search_c(envi[i], '=') != 0)
		return (0);
	free(envi[i]);
	envi[i] = ft_strdup(var);
	return (0);
}

static int	export_with_equals(char **envi, char *var, int len)
{
	int	i;
	int	eq_pos;

	i = 0;
	eq_pos = search_c(var, '=');
	while (envi[i])
	{
		if (ft_strncmp(envi[i], var, eq_pos) == 0
			&& (envi[i][eq_pos] == '=' || !envi[i][eq_pos]))
			return (check_and_replace(envi, var, i));
		else if (ft_strncmp(envi[i], var, len) == 0 && envi[i][len] == '=')
			return (check_and_replace(envi, var, i));
		else if (ft_strncmp(envi[i], var, len) == 0 && envi[i][len] == '\0')
			return (check_and_replace(envi, var, i));
		i++;
	}
	return (i);
}

int	ft_if_export(int i, char *var, char *equal_pos)
{
	char	**envi;
	int		len;

	if (check_identifier(var, i) == -1)
		return (-1);
	i = 0;
	(void)equal_pos;
	len = ft_strlen(var);
	envi = sim_glob(NULL, 'g');
	if (search_c(var, '=') != 0)
		return (export_with_equals(envi, var, len));
	else
	{
		while (envi[i])
		{
			if (ft_strncmp(envi[i], var, len) == 0 && envi[i][len] == '=')
				return (check_and_replace(envi, var, i));
			i++;
		}
	}
	return (i);
}

void	set_export(void)
{
	char	**env;
	char	**cpy;
	int		i;
	int		len;

	i = 0;
	env = sim_glob(NULL, 'g');
	len = ft_tablen(env);
	cpy = (char **)malloc(sizeof(char *) * (len + 1));
	while (i < len + 1)
	{
		cpy[i] = env[i];
		i++;
	}
	sim_glob(cpy, 'S');
	free(cpy);
}
