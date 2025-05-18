/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:24:19 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc/_malloc.h>
#include "../minishell.h"
#include "../../libft/libft.h"

static char	*ft_get_env(char *substr, int *i, t_data *data)
{
	char	*env;
	char	*tmp;

	tmp = trim_env(substr + 1, i);
	*i += 1;
	if (tmp[0] == '?')
	{
		env = ft_itoa(data->exit_status);
		free_string(tmp);
		return (env);
	}
	env = ft_search_env(tmp, data);
	free_string(tmp);
	return (env);
}

static int	find_len(char *line, t_data *data)
{
	int		i;
	int		len;
	char	*env;

	i = 0;
	len = 0;
	while (line[i] != '\0')
	{
		if (is_question_mark(line[i], line[i + 1])
			&& !is_sinquote(line, i))
		{
			env = ft_get_env(line + i, &i, data);
			if (!env)
				continue ;
			if (env)
				len += ft_strlen(env);
			free_string(env);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static char	*ft_copier(char *line, int j, int k, t_data *data)
{
	int	len;

	len = find_len(line, data);
	data->var.str = (char *)ft_calloc(sizeof(char), len + 1);
	if (!data->var.str)
		return (NULL);
	while (line[j])
	{
		if (is_question_mark(line[j], line[j + 1]) && !is_sinquote(line, j))
		{
			data->var.env = ft_get_env(line + j, &j, data);
			if (data->var.env)
				data->var.str = ft_strjoin(data->var.str, data->var.env, len);
			if (data->var.env)
				k += ft_strlen(data->var.env);
			free_string(data->var.env);
		}
		else
		{
			data->var.str[k] = line[j++];
			data->var.str[++k] = '\0';
		}
	}
	return (data->var.str);
}

t_expand	*ft_expander(char **line, int i, int j, t_data *data)
{
	t_expand	*exped;
	char		*str;
	char		*after_dollar;
	int			k;

	exped = NULL;
	while (line[i])
	{
		after_dollar = ft_strchr(line[i], '$');
		j = 0;
		k = 0;
		if (!after_dollar)
			exped = ft_add_back_expander(exped, line[i]);
		else
		{
			str = ft_copier(line[i], j, k, data);
			exped = ft_add_back_expander(exped, str);
			free_string(str);
		}
		i++;
	}
	return (exped);
}
