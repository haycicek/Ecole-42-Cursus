/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:22:15 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc/_malloc.h>
#include "../minishell.h"
#include "../../libft/libft.h"

t_expand	*ft_add_back_expander(t_expand *head, char *str)
{
	t_expand	*tmp;
	t_expand	*new;

	tmp = NULL;
	new = NULL;
	tmp = head;
	new = (t_expand *)malloc(sizeof(t_expand));
	new->str = ft_strdup(str);
	if (new->str == NULL)
		return (NULL);
	new->next = NULL;
	if (!(head))
		head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (head);
}

char	*ft_search_env(char *splitted_input, t_data *data)
{
	char	*str;
	t_env	*tmp;

	str = NULL;
	tmp = NULL;
	tmp = data->environmental;
	if (!splitted_input || *splitted_input == '\0')
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(splitted_input, tmp->key,
				ft_strlen(splitted_input)) == 0)
		{
			str = ft_strdup(tmp->value);
			return (str);
		}
		tmp = tmp->next;
	}
	return (str);
}

int	is_question_mark(char c, char x)
{
	return ((c == '$' && (ft_isalnum(x) || x == '?' || x == '_')));
}

int	is_sinquote(char *str, int indx)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (i < indx)
	{
		if (str[i] == '\'')
			flag++;
		i++;
	}
	if (flag && flag % 2 == 0)
		return (0);
	else if (ft_strchr(str + indx + 1, '\'') != 0)
		return (1);
	return (0);
}
