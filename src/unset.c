/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:03:45 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/12 15:42:32 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static	int	ft_unset_env(char *name, char ***env)
// {
// 	char	**new_env;
// 	char	**env_ptr;
// 	int		len_env;
// 	int		len_name;

// 	if (!name)
// 		return (-1);
// 	len_name = ft_strlen(name);
// 	env_ptr = *env;
// 	while (*env_ptr)
// 	{
// 		if (ft_strncmp(*env_ptr, name, len_name) == 0 && (*env_ptr)[len_name] == '=')
// 		{
// 			return (0);
// 		}
// 		env_ptr++;
// 	}
// 	return (0);
// }

void	exec_unset(char **command, char ***env)
{
	(void)env;
	(void)command;
	return ;
	if (command && command[1])
	{
		//ft_unset_env(command[1], env);
	}
	else
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
	}
}
