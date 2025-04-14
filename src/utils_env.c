/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:55:00 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/14 13:54:27 by tle-saut         ###   ########.fr       */
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

char	*search_replace(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			str[i] = ' ';
		i++;
	}
	return (str);
}

void	set_mini_env(void)
{
	char	**tab;
	int		fd;
	char	*str;
	char	*buff;

	buff = NULL;
	fd = open("/etc/environment", O_RDONLY);
	tab = sim_glob(NULL, 'g');
	tab = malloc(sizeof(char *) * 5);
	str = get_next_line(fd);
	str = search_replace(str, '\"');
	buff = getcwd(buff, 0);
	tab[0] = ft_strdup(ft_substr(str, 0, ft_strlen(str) - 4));
	tab[1] = ft_strdup("OLDPWD");
	tab[2] = ft_strdup(ft_strjoin("PWD=", buff));
	free(buff);
	tab[3] = ft_strdup("SHLVL=1");
	tab[4] = 0;
	sim_glob(tab, 's');
}

void	get_env(char **envp)
{
	int		i;
	char	**cpy_env;

	if (ft_tablen(envp) < 1)
		return (set_mini_env());
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
