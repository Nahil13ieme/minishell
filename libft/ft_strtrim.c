/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:25:09 by nbenhami          #+#    #+#             */
/*   Updated: 2024/11/07 12:09:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;
	char		*trimmed;
	size_t		i;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	start = s1;
	while (*s1)
		s1++;
	end = s1 - 1;
	while (end >= start && ft_strchr(set, *end))
		end--;
	trimmed = (char *)malloc((end - start + 1) + 1);
	if (trimmed == NULL)
		return (NULL);
	i = 0;
	while (i < (size_t)(end - start + 1))
	{
		trimmed[i] = start[i];
		i++;
	}
	trimmed[(end - start + 1)] = '\0';
	return (trimmed);
}
