/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:56:40 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/12 15:19:47 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_my_env(char **env, char *name)
{
	int		len_name;
	char	**ptr;

	if (!env || !name)
		return (NULL);
	len_name = ft_strlen(name);
	ptr = env;
	while (*ptr)
	{
		if (ft_strncmp(*ptr, name, len_name) == 0 && (*ptr)[len_name] == '=')
		{
			return (*ptr + len_name + 1);
		}
		ptr++;
	}
	return (NULL);
}

void	exec_env(char **env)
{
	while (env && *env)
	{
		printf("%s\n", *env);
		env++;
	}
}
