/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:24:33 by nbenhami          #+#    #+#             */
/*   Updated: 2024/11/06 15:24:36 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, char const *src, unsigned int size)
{
	unsigned int	dest_l;
	unsigned int	src_l;
	unsigned int	result;
	unsigned int	i;

	dest_l = ft_strlen(dest);
	src_l = ft_strlen(src);
	result = 0;
	if (size > dest_l)
		result = src_l + dest_l;
	else
		result = src_l + size;
	if (size == 0)
		return (result);
	i = 0;
	while (src[i] && dest_l < size - 1)
	{
		dest[dest_l] = src[i];
		dest_l++;
		i++;
	}
	dest[dest_l] = '\0';
	return (result);
}
