/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:30:40 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <malloc/_malloc.h>
#include "../minishell.h"
#include "../../libft/libft.h"

static char	*ft_getenv(char *str, t_data	*data)
{
	t_env	*env;

	env = data->environmental;
	if (!str)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	get_cd_path(t_cmd *cmd, char **path, t_data *data)
{
	if (cmd->args[1] == NULL || ft_strcmp(cmd->args[1], "~") == 0)
	{
		*path = ft_getenv("HOME", data);
		if (*path == NULL)
			return (0);
	}
	else
		*path = cmd->args[1];
	ft_change_env("OLDPWD", ft_getenv("PWD", data), 0, data);
	ft_change_env("OLDPWD", ft_getenv("PWD", data), 1, data);
	return (1);
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	*pwd;

	if (cmd->args[1] && cmd->args[2])
		return (printf("minishell: cd: too many arguments\n"), -1);
	if (get_cd_path(cmd, &path, data) == 0)
		return (0);
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	pwd = getcwd(NULL, 0);
	ft_change_env("PWD", pwd, 0, data);
	free(pwd);
	return (0);
}
