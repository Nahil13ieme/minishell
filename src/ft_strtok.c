/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:04:00 by nbenhami          #+#    #+#             */
/*   Updated: 2025/03/08 00:57:44 by nbenhami         ###   ########.fr       */
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
	static char	*str_new;
	int			i;
	int			size_ret;

	if (str != NULL)
	{
		str_new = str;
	}
	else
	{
		str = str_new;
	}
	i = 0;
	size_ret = 0;
	if (!str_new || !str)
		return (NULL);
	while (str[i] && ft_check_separators(separators, str[i]))
		i++;
	while (str[i] && !ft_check_separators(separators, str[i]))
	{
		i++;
		size_ret++;
	}
	ret = malloc(sizeof(char) * size_ret + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str + i - size_ret, size_ret + 1);
	str_new = str + i;
	if (*str_new == '\0')
		str_new = NULL;
	return (ret);
}
