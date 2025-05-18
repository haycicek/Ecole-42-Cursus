/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:13:01 by haycicek          #+#    #+#             */
/*   Updated: 2023/01/19 14:17:10 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexabas(unsigned int nbr)
{
	int	i;

	i = 0;
	while (nbr != 0)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}

void	ft_printhexa(char c, unsigned int n)
{
	if (n >= 16)
	{
		ft_printhexa(c, n / 16);
		ft_printhexa(c, n % 16);
	}
	else if (n <= 9)
		ft_putchar(n + 48);
	else if (c == 'x' && n >= 10 && n <= 15)
		ft_putchar(n + 87);
	else if (c == 'X' && n >= 10 && n <= 15)
		ft_putchar(n + 55);
}

int	ft_hexa(char c, unsigned int nbr)
{
	int	i;

	i = ft_hexabas(nbr);
	if (nbr == 0)
	{
		ft_putchar('0');
		return (1);
	}
	ft_printhexa(c, nbr);
	return (i);
}
