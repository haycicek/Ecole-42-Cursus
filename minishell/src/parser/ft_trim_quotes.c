/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:28:38 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"

static int	ft_get_trim_len(char *str, char *quote, int i, int len)
{
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			*quote = str[i];
			i++;
			while (str[i] != '\0')
			{
				if (str[i] == *quote)
					break ;
				i++;
				len++;
			}
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*ft_trim_quotes(char *str, int i, int len)
{
	char	quote;
	char	*res;

	len = ft_get_trim_len(str, &quote, 0, 0);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] != '\0')
			{
				if (str[i] == quote)
					break ;
				res[len++] = str[i++];
			}
		}
		else
			res[len++] = str[i++];
	}
	res[len] = '\0';
	return (res);
}
