/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:49:35 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/13 11:16:03 by nbenhami         ###   ########.fr       */
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
			write(1, &args[i][j], 1);
			j++;
		}
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	return (i);
}

int	ft_if_export(int i, char *var, char *equal_pos)
{
	char	**envi;
	int		len;

	(void)equal_pos;
	len = ft_strlen(var);
	envi = sim_glob(NULL, 'g');
	if (search_c(var, '=') != 0)
	{
		while (envi[i])
		{
			if (ft_strncmp(envi[i], var, search_c(var, '=')) == 0
				&& (envi[i][search_c(var, '=')] == '='
				|| !envi[i][search_c(var, '=')]))
			{
				if (search_c(var, '=') == 0 && search_c(envi[i], '=') != 0)
					return (0);
				free(envi[i]);
				envi[i] = ft_strdup(var);
				return (0);
			}
			else if (ft_strncmp(envi[i], var, len) == 0 && envi[i][len] == '=')
			{
				if (search_c(var, '=') == 0 && search_c(envi[i], '=') != 0)
					return (0);
				free(envi[i]);
				envi[i] = ft_strdup(var);
				return (0);
			}
			else if (ft_strncmp(envi[i], var, len) == 0 && envi[i][len] == '\0')
			{
				if (search_c(var, '=') == 0 && search_c(envi[i], '=') != 0)
					return (0);
				{
					free(envi[i]);
					envi[i] = ft_strdup(var);
					return (0);
				}
				i++;
			}
			i++;
		}
	}
	else
	{
		while (envi[i])
		{
			if (ft_strncmp(envi[i], var, len) == 0 && envi[i][len] == '=')
			{
				if (search_c(var, '=') == 0 && search_c(envi[i], '=') != 0)
					return (0);
				free(envi[i]);
				envi[i] = ft_strdup(var);
				return (0);
			}
			i++;
		}
	}
	return (i);
}

void	export_pwd(char *buff)
{
	char	*tempold;
	char	*temp;
	char	*pwd;
	int		freeint;

	freeint = 0;
	pwd = return_env("PWD");
	buff = getcwd(buff, 0);
	if (buff == NULL)
	{
		buff = pwd;
		freeint = 1;
	}
	tempold = ft_strjoin("OLDPWD=", pwd);
	ft_unset("OLDPWD", 0);
	ft_export(tempold, 0);
	temp = ft_strjoin("PWD=", buff);
	ft_export(temp, 0);
	if (freeint == 0)
		return (free(temp), free(tempold), free(buff), free(pwd));
	return (free(temp), free(tempold), free(pwd));
}

int	search_c(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (i);
		i++;
	}
	return (0);
}
