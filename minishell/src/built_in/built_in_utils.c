/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:30:32 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc/_malloc.h>
#include "../minishell.h"
#include "../../libft/libft.h"

void	ft_delete_env(char *str, t_data	*data)
{
	t_env	*env;
	t_env	*prev;

	env = data->environmental;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			if (prev == NULL)
				data->environmental = env->next;
			else
				prev->next = env->next;
			free_env_node(env);
			free_array(data->env);
			data->env = ft_env_to_matrix(data);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

void	ft_delete_export(char *str, t_data	*data)
{
	t_env	*env;
	t_env	*prev;

	env = data->export;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			if (prev == NULL)
				data->export = env->next;
			else
				prev->next = env->next;
			free_env_node(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

void	ft_new_env(char *str, int choose, t_data *data)
{
	t_env	*env;
	t_env	*new;

	if (choose == 0)
		env = data->environmental;
	else
		env = data->export;
	new = (t_env *)malloc(sizeof(t_env));
	new->key = ft_substr(str, 0, ft_strchr(str, '=') - str);
	new->value = ft_substr(str, ft_strchr(str, '=') - str + 1, ft_strlen(str));
	new->next = NULL;
	if (env == NULL)
	{
		if (choose == 0)
			data->environmental = new;
		else
			data->export = new;
	}
	else
	{
		while (env->next)
			env = env->next;
		env->next = new;
	}
}

int	ft_is_valid_env(char *str, int choose, t_data	*data)
{
	t_env	*env;

	if (choose == 0)
		env = data->environmental;
	else
		env = data->export;
	if (!str)
		return (0);
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_change_env(char *str, char *new_value, int choose, t_data *data)
{
	t_env	*env;

	if (choose == 0)
		env = data->environmental;
	else
		env = data->export;
	if (!str)
		return ;
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(new_value);
			return ;
		}
		env = env->next;
	}
}
