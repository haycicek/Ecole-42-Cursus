/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:14:34 by haycicek          #+#    #+#             */
/*   Updated: 2023/01/19 14:14:41 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int i)
{
	char	*s;
	int		a;

	if (i == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	else
		s = ft_itoa(i);
	a = ft_putstr(s);
	free(s);
	return (a);
}
