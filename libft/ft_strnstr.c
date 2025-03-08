/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:24:58 by nbenhami          #+#    #+#             */
/*   Updated: 2024/11/07 12:03:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *haystack, char const *needle, size_t n)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (n && *haystack)
	{
		if (n < needle_len)
		{
			return (NULL);
		}
		if (*haystack == *needle && !ft_memcmp(haystack, needle, needle_len))
		{
			return ((char *)haystack);
		}
		haystack++;
		n--;
	}
	return (NULL);
}
