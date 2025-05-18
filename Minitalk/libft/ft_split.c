/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:40:09 by haycicek          #+#    #+#             */
/*   Updated: 2023/02/17 14:40:12 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	wordcounter(const char *s, char delimiter)
{
	unsigned int	word;

	word = 0;
	while (*s)
	{
		if (*s == delimiter)
			s++;
		else
		{
			while (*s != delimiter && *s)
				s++;
			word++;
		}
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char			**arr;
	unsigned int	j;
	unsigned int	a;

	if (!s)
		return (NULL);
	arr = (char **) ft_calloc(wordcounter(s, c) + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	a = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			j = 0;
			while (*s != c && *s && ++j)
				s++;
			arr[++a -1] = (char *) ft_calloc(j + 1, sizeof(char));
			ft_strlcpy(arr[a -1], s - j, j + 1);
		}
	}
	return (arr);
}
