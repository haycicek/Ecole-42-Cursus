/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:11:50 by haycicek          #+#    #+#             */
/*   Updated: 2023/01/19 14:12:11 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char a)
{
	write(1, &a, 1);
	return (1);
}

int	ft_format(va_list arg, int c)
{
	int	i;

	i = 0;
	if (c == '%')
		i += ft_putchar('%');
	else if (c == 'c')
		i += ft_putchar(va_arg(arg, int));
	else if (c == 'i' || c == 'd')
		i += ft_putnbr(va_arg(arg, int));
	else if (c == 's')
		i += ft_putstr(va_arg(arg, char *));
	else if (c == 'p')
		i += ft_ptr(va_arg(arg, unsigned long long));
	else if (c == 'u')
		i += ft_unsignedint(va_arg(arg, unsigned int));
	else if (c == 'x' || c == 'X')
		i += ft_hexa(c, va_arg(arg, unsigned int));
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;
	int		len;

	va_start(arg, str);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			len += ft_format(arg, str[i]);
		}
		else
			len += ft_putchar (str[i]);
		i++;
	}
	va_end(arg);
	return (len);
}
