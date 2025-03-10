/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:04:00 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/10 02:25:33 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_check_separators(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtok(char *str, char *separators)
{
	char		*ret;
	static char	*str_new = NULL;

	if (str != NULL)
		str_new = str;
	else if (str_new == NULL)
		return (NULL);
	while (*str_new && ft_check_separators(separators, *str_new))
		str_new++;
	if (*str_new == '\0')
	{
		str_new = NULL;
		return (NULL);
	}
	ret = str_new;
	while (*str_new && !ft_check_separators(separators, *str_new))
		str_new++;
	if (*str_new)
		*str_new++ = '\0';
	return (ret);
}
