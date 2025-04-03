/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:49:35 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 15:59:20 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_while_echo(char **args, int i, int j)
{
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			printf("%c", args[i][j]);
			j++;
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
	return (i);
}

int	ft_if_export(char **envi, int i, char *var, char *equal_pos)
{
	if (equal_pos)
	{
		while (envi[i])
		{
			if (ft_strncmp(envi[i], var, equal_pos - var) == 0)
			{
				free(envi[i]);
				envi[i] = ft_strdup(var);
				return ;
			}
			i++;
		}
	}
	else
	{
		i = 0;
		while (envi[i])
			i++;
	}
	return (i);
}

void	ft_if_unset(char **envp, char **export, char *var, int len, int i)
{
	int	j;

	j = 0;
	if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
	{
		j = i;
		free(envp[i]);
		while (envp[j])
		{
			envp[j] = envp[j + 1];
			j++;
		}
		return ;
	}
	if (ft_strncmp(export[i], var, len) == 0)
	{
		j = i;
		free(export[i]);
		while (export[j])
		{
			export[j] = export[j + 1];
			j++;
		}
		return ;
	}
}
