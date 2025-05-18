/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:49:20 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"
#include "../../libft/libft.h"

static char	get_new_matrix(char **matrix, t_env *env, int i)
{
	while (env)
	{
		matrix[i] = ft_strdup(env->key);
		matrix[i] = ft_strjoin(matrix[i], "=", ft_strlen(matrix[i]) + 1);
		matrix[i] = ft_strjoin(matrix[i], env->value,
				ft_strlen(matrix[i]) + ft_strlen(env->value));
		env = env->next;
		i++;
	}
	matrix[i] = NULL;
	return (1);
}

char	**ft_env_to_matrix(t_data *data)
{
	t_env	*env;
	char	**matrix;
	int		i;

	env = data->environmental;
	i = 0;
	while (env->next)
	{
		i++;
		env = env->next;
	}
	matrix = malloc(sizeof(char *) * (i + 2));
	if (!matrix)
		return (NULL);
	i = 0;
	env = data->environmental;
	if (!get_new_matrix(matrix, env, i))
		return (NULL);
	return (matrix);
}

int	ft_unset(t_cmd *cmd, t_data	*data)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (ft_is_valid_env(cmd->args[i], 0, data))
			ft_delete_env(cmd->args[i], data);
		if (ft_is_valid_env(cmd->args[i], 1, data))
			ft_delete_export(cmd->args[i], data);
		i++;
	}
	return (0);
}
