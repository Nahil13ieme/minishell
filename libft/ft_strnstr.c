/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:24:58 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/01 15:24:01 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


/**
 * The strnstr() function locates the first occurrence of the null-terminated
 * string needle in the string haystack, where not more than n characters are
 * searched.  Characters that appear after a `\0' character are not searched.
 * @return a pointer to the beginning of the located string, or NULL if the
 */
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
