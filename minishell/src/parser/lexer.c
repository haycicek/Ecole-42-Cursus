/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:27:44 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"
#include "../../libft/libft.h"

static int	ft_words_nbr(char *str, int i, int counter)
{
	char	quote;

	quote = 0;
	while (str[i] != '\0')
	{
		quote = 0;
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (str[i] && ft_is_quote(str[i]))
		{
			counter++;
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			i++;
			while (str[i] != '\0' && !ft_is_delimiter(str[i])
				&& !ft_is_quote(str[i]))
				i++;
		}
		else if (str[i] && !ft_is_delimiter(str[i]) && counter++ > -1)
			i = find_len_util(str, i, quote);
	}
	return (counter);
}

static char	*ft_get_word_quote(char *str, char quote)
{
	int		i;
	char	*word;
	int		len;

	i = 1;
	while (str[i] != '\0' && str[i] != quote)
		i++;
	if (str[i])
		i++;
	while (str[i] != '\0' && !ft_is_delimiter(str[i])
		&& !ft_is_quote(str[i]))
		i++;
	len = i;
	if (i == 0)
		return (NULL);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (++i < len)
		word[i] = str[i];
	word[i] = '\0';
	return (word);
}

static char	*ft_get_word(char *str, int a, int i, char is_quote)
{
	char	*word;

	word = (char *)malloc(sizeof(char) * (ft_get_word_len(str) + 1));
	if (!word)
		return (NULL);
	while (str[i] != '\0' && (!ft_is_delimiter(str[i]) || is_quote > 0))
	{
		if (str[i + 1] && ((a % 2 == 0 && str[i + 1] == ' ')
				|| (is_quote > 0 && is_quote == str[i] && str[i + 1] == ' ')))
		{
			word[i] = str[i];
			i++;
			break ;
		}
		if (ft_is_quote(str[i]))
		{
			is_quote = str[i];
			a++;
		}
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	*lex_with_type(char *str, char **split, int i)
{
	char	*ret;

	if (ft_is_quote(*str))
	{
		ret = ft_get_word_quote(str, *str);
		if (ret)
			split[i] = ret;
		str += ft_strlen(ret);
	}
	else
	{
		ret = ft_get_word(str, 0, 0, 0);
		if (ret)
			split[i] = ret;
		str += ft_strlen(ret);
	}
	return (str);
}

char	**ft_lexer(char *str, int i)
{
	char	**split;

	split = (char **)malloc(sizeof(char *) * (ft_words_nbr(str, 0, 0) + 1));
	if (!split)
		return (NULL);
	while (*str && (*str || ft_is_delimiter(*str)))
	{
		while (*str && ft_is_delimiter(*str))
			str++;
		if (*str && !ft_is_delimiter(*str))
		{
			str = lex_with_type(str, split, i);
			i++;
		}
	}
	split[i] = NULL;
	return (split);
}
