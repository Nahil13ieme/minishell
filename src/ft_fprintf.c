/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:37:33 by tle-saut          #+#    #+#             */
/*   Updated: 2025/04/08 14:21:28 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_fprintstr(char *str)
{
	if (str == NULL)
		return (ft_printstr("(null)"));
	return (write(2, str, ft_strlen(str)));
}

static int	ft_fprintfnumb(int n)
{
	int	cpt;

	cpt = 0;
	if (n == -2147483648)
	{
		cpt += write(2, "-2147483648", 11);
	}
	else
	{
		if (n < 0)
		{
			n = n * -1;
			cpt += write(2, "-", 1);
		}
		if (n >= 10)
		{
			cpt += ft_printfnumb(n / 10);
		}
		n = (n % 10) + 48;
		cpt += write(2, &n, 1);
	}
	return (cpt);
}

static int	ft_fprintchar(char c)
{
	return (write(2, &c, 1));
}

static int	ft_fcheck(va_list args, char c)
{
	unsigned int	cpt;

	cpt = 0;
	if (c == 'c')
		cpt += ft_printchar(va_arg(args, int));
	else if (c == 's')
		cpt += ft_printstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		cpt += ft_printfnumb(va_arg(args, int));
	return (cpt);
}

unsigned int	ft_fprintf(const char *str, ...)
{
	unsigned int	cpt;
	va_list			args;

	va_start(args, str);
	cpt = 0;
	while (*str)
	{
		if (*str != '%')
		{
			cpt += write(2, str, 1);
			str++;
		}
		else
		{
			str++;
			cpt += ft_check(args, *str);
			str++;
		}
	}
	va_end(args);
	return (cpt);
}