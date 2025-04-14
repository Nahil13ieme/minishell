/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:18:53 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/14 08:26:57 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Commande built-in pour changer de repertoire.
 * @param path Nouveau chemin desirer. en char *
 */
int	ft_cd(char **args)
{
	char	*home;
	char	*pwd;

	home = return_env("HOME");
	pwd = return_env("PWD");
	if (args[1] == NULL)
	{
		if (home == NULL)
			return (free(pwd), ft_fprintf("cd : HOME not set\n"));
		chdir(home);
		export_pwd("");
	}
	else if (args[1][0] == '~')
		return (chdir(home), free(home), free(pwd), 0);
	else if (!args[2] && chdir(args[1]) == 0)
	{
		export_pwd("");
		return (free(home), free(pwd), 0);
	}
	else if (chdir(args[1]) == -1)
		ft_fprintf("minishell: cd: %s: No such file or directory\n", args[1]);
	else if (args[2])
		ft_fprintf("minishell: cd: too many arguments\n");
	return (free(home), free(pwd), 1);
}
