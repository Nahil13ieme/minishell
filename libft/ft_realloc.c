/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:38:12 by nbenhami          #+#    #+#             */
/*   Updated: 2025/02/27 15:37:59 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*ret;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	ret = malloc(new_size);
	if (!ret)
		return (NULL);
	if (!ptr)
		return (ret);
	if (new_size > old_size)
		new_size = old_size;
	ft_memcpy(ret, ptr, new_size);
	free(ptr);
	return (ret);
}
