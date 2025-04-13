/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:49:35 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/13 19:05:44 by tle-saut         ###   ########.fr       */
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
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	return (i);
}

int	ft_if_export(int i, char *var, char *equal_pos)
{
	char	**envi;
	int		len;
	int		before;

	before = 0;
	while (var[i])
	{
		if (var[i] == '=')
			before = 1;
		if ((var[i] < 48 || var[i] > 57) && (var[i] < 65 || var[i] > 90) && (var[i] < 97 || var[i] > 122) && before == 0)
			return (ft_fprintf("minishell: export: %s not a valid identifier\n",
				var), 0);
		i++;
	}
	i = 0;
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

void	export_pwd(char *buf)
{
	char	*cwd;
	char	*oldpwd;
	char	*env_pwd;
	char	*pwd_entry;

	(void)buf;
	env_pwd = return_env("PWD");
	if (env_pwd)
		oldpwd = ft_strjoin("OLDPWD=", env_pwd);
	else
		oldpwd = ft_strjoin("OLDPWD=", "");
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(oldpwd));
	pwd_entry = ft_strjoin("PWD=", cwd);
	ft_unset("OLDPWD", 0);
	ft_export(oldpwd, 0);
	ft_export(pwd_entry, 0);
	free(env_pwd);
	free(oldpwd);
	free(pwd_entry);
	free(cwd);
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
