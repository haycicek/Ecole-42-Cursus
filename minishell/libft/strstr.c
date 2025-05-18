/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:27:23 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *big, char *little)
{
	int	i;
	int	j;
	int	l_i;

	i = -1;
	if (!big)
		return (0);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[++i])
	{
		l_i = 0;
		if (big[i] == little[l_i])
		{
			j = i;
			while (big[j] == little[l_i])
			{
				l_i++;
				j++;
				if (little[l_i] == '\0')
					return ((char *)(big + i));
			}
		}
	}
	return (0);
}
