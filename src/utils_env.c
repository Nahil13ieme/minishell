/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:55:00 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 20:06:02 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_env(char **envp)
{
	int		i;
	char	**cpy_env;

	i = 0;
	while (envp[i])
		i++;
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
	cpy_env[i] = NULL;
	sim_glob(cpy_env, 's');
	set_export();
	set_path();
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

	len = ft_strlen(str);
	env = sim_glob(NULL, 'g');
	i = 0;

	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

