/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:49:35 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/04 15:59:45 by tle-saut         ###   ########.fr       */
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
			if (args[i][j] == '$' && args[i][j + 1] == '?')
			{
				printf("%d", get_exit_code());
				j++;
			}
			else
			{
				printf("%c", args[i][j]);
			}
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
				return (0);
			}
			i++;
		}
	}
	else
		while (envi[i])
		{
			if (ft_strncmp(envi[i], var, ft_strlen(var)) == 0)
				{
					free(envi[i]);
					envi[i] = ft_strdup(var);
					return (0);
				}
			i++;
		}
	return (i);
}

void	ft_if_unset(char **export, char *var, int len, int i)
{
	char	**envp;

	envp = sim_glob(NULL, 'g');
	if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
	{
		free(envp[i]);
		while (envp[i])
		{
			if (envp[i + 1])
				envp[i] = envp[i + 1];
			i++;
		}
		return ;
	}
	if (ft_strncmp(export[i], var, len) == 0)
	{
		free(export[i]);
		while (export[i])
		{
			if(export[i + 1])
				export[i] = export[i + 1];
			i++;
		}
		return ;
	}
}
