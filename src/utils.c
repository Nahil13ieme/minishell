/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:17:41 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 15:56:05 by tle-saut         ###   ########.fr       */
=======
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:17:41 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/03 15:54:56 by nbenhami         ###   ########.fr       */
>>>>>>> 2008d0b9206332326cfc913d004775c515070950
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

<<<<<<< HEAD
=======
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

>>>>>>> 2008d0b9206332326cfc913d004775c515070950
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
<<<<<<< HEAD
=======
		{
			free(tab[i]);
			i++;
		}
	free(tab);
}

void	free_glob()
{
	sim_glob(NULL, 'f');
}

char	**sim_glob(char **tab, char c)
{
	static char	**export = NULL;
	static char	**env = NULL;
	if (c == 'g')
		return (env);
	else if (c == 'G')
		return (export);
	else if (c == 's')
		env = tab;
	else if (c == 'S')
		export = tab;
	else if (c == 'f')
	{
		if (env)
        {
            for (int i = 0; env[i]; i++)
            {
                if (ft_strncmp(env[i], "PATH=", 5) == 0)
                {
                    free(env[i]);
                }
            }
            free(env);
            env = NULL;
        }
        if (export)
        {
            for (int i = 0; export[i]; i++)
            {
                if (ft_strncmp(export[i], "PWD=", 4) == 0)
                {
                    free(export[i]);
                }
            }
            free(export);
            export = NULL;
        }
	}
	return (NULL);
}

char	**ft_tab_realloc(char **tab, size_t new_size)
{
	size_t	old_size;
	char	**new_tab;
	size_t	i;

	i = 0;
	old_size = 0;
	while (tab && tab[old_size])
		old_size++;
	new_tab = (char **)malloc(sizeof(char *) * (old_size + new_size + 1));
	if (!new_tab)
		return NULL;
	while (i < old_size)
>>>>>>> 2008d0b9206332326cfc913d004775c515070950
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_print_env(int export)
{
	char	**tab;
	int		i;
	int		j;
	int		pass;

	pass = 0;
	j = 0;
	i = 0;
	if (export == 0)
		tab = sim_glob(NULL, 'g');
	if (export == 1)
		tab = sim_glob(NULL, 'G');
	while (tab[i])
	{
		j = 0;
		if (export == 0)
			if (ft_strchr(tab[i], '=') != NULL)
				printf("%s\n", tab[i]);
		if (export == 1)
		{
			ft_while_print_export(tab, i, j);
		}
		i++;
	}
}

int	contain_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (1);
		else
			i++;
	}
	return (0);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
