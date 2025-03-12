/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:58:12 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/12 15:53:20 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_set_env(char *name, char *value, char ***env)
{
	char	**new_env;
	char	*env_entry;
	char	**env_ptr;
	int		exist;
	int		len_env;

	exist = 0;
	if (!name || !value || name[0] == '\0') 
		return -1;
	env_ptr = *env;
	while (*env_ptr)
	{
		if (ft_strncmp(*env_ptr, name, ft_strlen(name)) == 0 && (*env_ptr)[ft_strlen(name)] == '=')
		{
			exist = 1;
			break;
		}
		env_ptr++;
	}
	env_entry = ft_strjoin(name, "=");
	if (!env_entry)
		return -1;
	env_entry = ft_strjoin(env_entry, value);
	if (!env_entry)
		return -1;
	if (exist)
	{
		free(*env_ptr);
		*env_ptr = env_entry;
	}
	else
	{
		len_env = 0;
		env_ptr = *env;
		while (*env_ptr)
		{
			len_env++;
			env_ptr++;
		}
		new_env = malloc((len_env + 2) * sizeof(char *));
		if (!new_env)
			return -1;
		
		ft_memcpy(new_env, *env, len_env * sizeof(char *));
		new_env[len_env] = env_entry;
		new_env[len_env + 1] = NULL;
		*env = new_env;
	}
	return (0);
}

void	exec_export(char ***env, char **command)
{
	char	**env_ptr;

	env_ptr = *env;
	if (command && !command[1])
	{
		while(*env_ptr)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(*env_ptr, 1);
			ft_putchar_fd('\n', 1);
			env_ptr++;
		}
	}
	else
	{
		if (ft_set_env(command[1], command[2], env) == -1)
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(command[0], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
	}
}
