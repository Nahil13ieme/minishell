/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:55:00 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/13 11:14:27 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_check_env(void)
{
	char	**tab;
	char	*str;
	char	*buff;

	buff = NULL;
	tab = sim_glob(NULL, 'g');
	if (ft_tablen(tab) < 1)
	{
		buff = getcwd(buff, 0);
		str = ft_strjoin("PWD=", buff);
		ft_export(str, 0);
	}
	sim_glob(tab, 's');
}

void	add_shellvl(void)
{
	int		nbr;
	char	*str;
	char	*ret;
	char	*env;

	env = return_env("SHLVL");
	if (!env)
		env = ft_strdup("0");
	nbr = ft_atoi(env);
	free(env);
	nbr++;
	str = ft_itoa(nbr);
	ft_unset("SHLVL", 0);
	ret = ft_strjoin("SHLVL=", str);
	ft_export(ret, 0);
	free(ret);
	free(str);
	ft_check_env();
}

void	get_env(char **envp)
{
	int		i;
	char	**cpy_env;

	i = ft_tablen(envp);
	cpy_env = malloc(sizeof(char *) * (i + 1));
	if (cpy_env == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		cpy_env[i] = ft_strdup(envp[i]);
		if (cpy_env[i] == NULL)
		{
			free_tab(cpy_env);
			break ;
		}
		i++;
	}
	cpy_env[i] = 0;
	sim_glob(cpy_env, 's');
	add_shellvl();
}

void	free_glob(void)
{
	sim_glob(NULL, 'f');
}

/**
 * @brief Commande built-in pour afficher les varaible de ENV.
 * @param envp Variable d environement.
 */
void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '=') != NULL)
			printf("%s\n", envp[i]);
		i++;
	}
}

char	*return_env(char *str)
{
	int		i;
	char	**env;
	int		len;
	char	*ret;

	len = ft_strlen(str);
	env = sim_glob(NULL, 'g');
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0 && env[i][len] == '=')
		{
			ret = ft_strdup(env[i] + len + 1);
			return (ret);
		}
		i++;
	}
	return (NULL);
}
