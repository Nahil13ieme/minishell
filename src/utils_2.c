/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:03:50 by toto              #+#    #+#             */
/*   Updated: 2025/03/28 17:03:58 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/**
 * @brief Pour balader le tableaux export
 * @param c 'g' pour le recuperer || autre pour le set
 */
char	**export_global(char **tab, char c)
{
	static char **export = NULL;
	if (c == 'g')
		return (export);
	else
		export = tab;
	return(NULL);
}
/**
 * @brief Recupere le tableaux export a n apeler qu une fois
 */
void	get_export(char **tab)
{
	char *begin;
	int i;

	i = 0;
	while (tab[i])
		i++;
	begin = "declare -x";
	tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_strjoin(begin, tab[i]);
		i++;
	}
	tab[i] = 0;
	export_global(tab, 's');
}
void	add_export(char *str)
{
	int i;
	char **tab;
	char *define;

	define = "define -x ";
	export_global(ft_tab_realloc(export_global(NULL, 'g'), 1), 's');
	tab = export_global(NULL, 'g');
	i = 0;
	while (tab[i])
		i++;
	i--;
	if (ft_strrchr(str, ft_strlen(str)) == 0)
		tab[i] = ft_strdup(str);
	else
		tab[i] = ft_strjoin(define , str);
	export_global(tab, 's');
	free(tab);
}
