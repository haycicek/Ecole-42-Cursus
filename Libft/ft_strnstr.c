/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:43:03 by haycicek          #+#    #+#             */
/*   Updated: 2023/02/17 14:43:06 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	s2_len;

	i = 0;
	s2_len = ft_strlen(needle);
	if (!s2_len)
		return ((char *)haystack);
	if (len != 0)
	{
		while (haystack[i] && i <= len - s2_len)
		{
			j = 0;
			while (needle[j] && needle[j] == haystack[i + j])
				j++;
			if (j == s2_len)
				return ((char *)&haystack[i]);
			i++;
		}
	}
	return (NULL);
}
