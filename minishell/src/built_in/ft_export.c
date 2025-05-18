/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:40:24 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc/_malloc.h>
#include "../minishell.h"
#include "../../libft/libft.h"

static void	ft_only_export(t_data *data)
{
	t_env	*tmp;

	tmp = data->export;
	while (tmp)
	{
		printf("declare -x %s", tmp->key);
		if (ft_strlen(tmp->value) != 0)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

void	only_key_add(char *str, int flag, t_data *data)
{
	t_env	*tmp;
	t_env	*new;

	tmp = data->export;
	new = (t_env *)malloc(sizeof(t_env));
	new->key = ft_strdup(str);
	if (flag == 0)
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(" ");
	new->next = NULL;
	if (tmp == NULL)
		data->export = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*first_value(char *str)
{
	char	*new;
	int		i;

	i = -1;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str)));
	while (str[++i] && str[i] != '=')
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

static int	ft_export_2(t_cmd *cmd, char *tmp, t_data *data)
{
	char	**split_input;
	char	*key;

	if (tmp && *(tmp + 1) == '\0')
	{
		key = first_value(cmd->args[1]);
		if (!ft_is_valid_env(key, 1, data))
			only_key_add(key, 1, data);
		else
			ft_change_env(key, " ", 1, data);
		free(key);
		return (0);
	}
	if (!tmp || *tmp == cmd->args[1][0] || ft_strcmp(cmd->args[1], "=") == 0)
		return (ft_error('e', cmd), -1);
	split_input = ft_split(cmd->args[1], '=');
	if (!ft_is_valid_env(split_input[0], 0, data))
		ft_new_env(cmd->args[1], 0, data);
	if (ft_is_valid_env(split_input[0], 1, data))
		ft_change_env(split_input[0], split_input[1], 1, data);
	else
		ft_new_env(cmd->args[1], 1, data);
	return (free_array(split_input), 0);
}

int	ft_export(t_cmd *cmd, t_data *data)
{
	char	*tmp;

	if (cmd->args[1] == NULL)
		return (ft_only_export(data), 0);
	tmp = ft_strstr(cmd->args[1], "=");
	if (!tmp && cmd->args[2] == NULL)
	{
		if (!ft_is_valid_env(cmd->args[1], 1, data))
			return (only_key_add(cmd->args[1], 0, data), 0);
		return (0);
	}
	ft_export_2(cmd, tmp, data);
	return (0);
}
