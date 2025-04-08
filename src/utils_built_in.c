/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:49:35 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/08 17:04:34 by nbenhami         ###   ########.fr       */
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

int	ft_if_export(int i, char *var, char *equal_pos)
{
	char	**envi;

	envi = sim_glob(NULL, 'g');
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
	tempold = ft_strjoin("OLDPWD=",pwd);
	ft_unset("OLDPWD");
	ft_export(tempold);
	temp = ft_strjoin("PWD=", buff);
	ft_export(temp);
	if (freeint == 0)
		return (free(temp), free(tempold), free(buff), free(pwd));
	return (free(temp), free(tempold), free(pwd));
}
