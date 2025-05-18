/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:11:10 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:44:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"

int	ft_arg_size(t_expand *exped)
{
	int	i;

	i = 0;
	while (exped && !ft_is_pipe(exped->str))
	{
		if (exped->str && !ft_is_redir(exped->str))
			i++;
		else if (exped->str && ft_is_redir(exped->str))
		{
			exped = exped->next;
		}
		exped = exped->next;
	}
	return (i);
}

char	**ft_load_args(t_expand **exped, t_cmd *cmd, int count, t_data *data)
{
	char	**args;
	int		i;

	i = -1;
	args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	while ((*exped) && !(ft_is_pipe((*exped)->str)))
	{
		if (ft_is_redir((*exped)->str))
		{
			if (handle_redir(cmd, exped, data) == -1)
				return (free_array(args), NULL);
		}
		else
		{
			args[++i] = ft_trim_quotes((*exped)->str, 0, 0);
			(*exped) = (*exped)->next;
		}
	}
	args[++i] = NULL;
	return (args);
}

int	ft_count_pipe(t_expand *exped)
{
	int	count;

	count = 0;
	while (exped)
	{
		if (exped->str && exped->str[0] == '|')
		{
			if (exped->next->str && exped->next->str[0] == '|')
				return (-1);
			count++;
		}
		exped = exped->next;
	}
	return (count);
}

int	ft_is_redir(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '>' || str[0] == '<')
		return (1);
	return (0);
}

int	ft_is_pipe(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '|')
		return (1);
	return (0);
}
