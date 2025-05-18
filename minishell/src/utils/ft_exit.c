/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek/mminga>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:32:41 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/06 02:32:41 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../minishell.h"

void	free_env_node(t_env *env)
{
	free_string(env->key);
	free_string(env->value);
	free(env);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		free_string(tmp->key);
		free_string(tmp->value);
		free(tmp);
	}
}

void	ft_exit(char *str, t_data	*data)
{
	free_env(data->environmental);
	free_env(data->export);
	free_array(data->env);
	free(data);
	printf("%s", str);
	exit(0);
}
