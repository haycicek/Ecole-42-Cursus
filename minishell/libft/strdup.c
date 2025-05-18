/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:26:57 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc/_malloc.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*dup;

	len = ft_strlen(s1) + 1;
	dup = malloc(sizeof(char) * len);
	if (!dup)
		return (0);
	return (ft_strlcpy(dup, s1, len), (char *)dup);
}
