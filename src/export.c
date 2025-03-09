/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:58:12 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/09 23:43:31 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_export(char **env)
{
	while (env && *env)
	{
		printf("declare -x %s\n", *env);
		env++;
	}
}
