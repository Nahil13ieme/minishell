/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:05:36 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/14 16:38:34 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_sort(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (str1[i] > str2[i])
		return (1);
	else
		return (0);
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

int	ft_if_execute_first(t_btree *tree)
{
	if (tree == NULL)
		return (1);
	if (tree->cmd && tree->cmd[0])
	{
		if (tree->cmd && strcmp(tree->cmd[0], "$?") == 0)
		{
			free(tree->cmd[0]);
			tree->cmd[0] = ft_itoa(get_exit_code());
		}
		tree->cmd = retrieve_var(tree->cmd, 0);
		if (tree->cmd)
		{
			if (tree->cmd[0][0] == 0)
			{
				tree->status = 0;
				return (1);
			}
			execute_path(tree);
		}
	}
	return (0);
}
