/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:26:56 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc/_malloc.h>
#include "../minishell.h"
#include "../../libft/libft.h"

char	*ft_strsub(char *str, int start, int end)
{
	char	*new;
	int		i;

	i = 0;
	if (end >= start)
	{
		new = (char *)malloc(sizeof(char) * (end - start + 1));
		if (!new)
			return (NULL);
	}
	else
		return (0);
	while (start < end)
	{
		new[i] = str[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}

static t_expand	*assign_to_struct(t_expand *head, t_expand *tmp,
		t_expand *tmp_next, char *str[3])
{
	t_expand	*new;
	t_expand	*new2;

	free(tmp->str);
	if (str[0][0] != '\0')
	{
		tmp->str = str[0];
		new = (t_expand *)malloc(sizeof(t_expand));
		if (!new)
			return (NULL);
		tmp->next = new;
		tmp = new;
	}
	tmp->str = str[1];
	if (str[2][0] != '\0')
	{
		new2 = (t_expand *)malloc(sizeof(t_expand));
		if (!new2)
			return (NULL);
		new2->str = str[2];
		tmp->next = new2;
		tmp = new2;
	}
	tmp->next = tmp_next;
	return (head);
}

static t_expand
	*ft_handle_special_signs(t_expand *head, t_expand *tmp, char *type)
{
	char	*str[3];
	int		idx;

	if (ft_strcmp(tmp->str, type) == 0)
		return (head);
	idx = ft_strchr(tmp->str, type[0]) - tmp->str;
	str[0] = ft_strsub(tmp->str, 0, idx);
	str[1] = ft_strdup(type);
	str[2] = ft_strsub(tmp->str, idx + ft_strlen(type), ft_strlen(tmp->str));
	head = assign_to_struct(head, tmp, tmp->next, str);
	idx = 0;
	while (idx < 3)
	{
		if (str[idx][0] == '\0')
			free(str[idx]);
		idx++;
	}
	return (head);
}

static t_expand	*check_special_char(t_expand *head, t_expand *tmp)
{
	int	i;

	i = 0;
	while (tmp->str[i] && tmp->str[i] == ' ')
		i++;
	while (tmp->str[i] && tmp->str[i] != '<' && tmp->str[i] != '>'
		&& tmp->str[i] != '|')
		i++;
	if (tmp->str[i] && tmp->str[i] == '<')
	{
		if (tmp->str[i + 1] == '<')
			return (ft_handle_special_signs(head, tmp, "<<"));
		else
			return (ft_handle_special_signs(head, tmp, "<"));
	}
	else if (tmp->str[i] && tmp->str[i] == '>')
	{
		if (tmp->str[i + 1] == '>')
			return (ft_handle_special_signs(head, tmp, ">>"));
		else
			return (ft_handle_special_signs(head, tmp, ">"));
	}
	else if (tmp->str[i] && tmp->str[i] == '|')
		return (ft_handle_special_signs(head, tmp, "|"));
	return (head);
}

t_expand	*ft_parser(t_expand *expander)
{
	t_expand	*head;
	t_expand	*tmp;

	tmp = expander;
	head = expander;
	while (tmp)
	{
		if (tmp->str[0] != '\"' && tmp->str[0] != '\'')
			head = check_special_char(head, tmp);
		tmp = tmp->next;
	}
	return (head);
}
