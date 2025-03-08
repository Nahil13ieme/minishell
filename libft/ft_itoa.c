/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:20:20 by nbenhami          #+#    #+#             */
/*   Updated: 2024/11/06 15:49:08 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

static int	get_length(int n)
{
	int	length;

	length = 0;
	if (n <= 0)
		length = 1;
	while (n)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int				length;
	char			*str;
	unsigned int	num;
	int				i;

	length = get_length(n);
	str = (char *)malloc(length + 1);
	if (str == NULL)
		return (NULL);
	num = n;
	if (n < 0)
	{
		num = -n;
		str[0] = '-';
	}
	str[length] = '\0';
	i = length - 1;
	if (num == 0)
		str[i] = '0';
	while (num)
	{
		str[i--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
