/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:26:28 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc/_malloc.h>
#include "../minishell.h"
#include "../../libft/libft.h"

static char	**ft_getenv(char **env, char *key)
{
	size_t	i;

	while (env && *env)
	{
		i = 0;
		while (*(*env + i) == key[i])
			i++;
		if (*(*env + i) == '=')
			return (ft_split(*env + i + 1, ':'));
		env++;
	}
	return (NULL);
}

static char	*join_path(char *path, char *file)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new = malloc(ft_strlen(path) + ft_strlen(file) + 2);
	if (!new)
		return (NULL);
	while (path[i])
	{
		new[i] = path[i];
		i++;
	}
	new[i++] = '/';
	while (file[j])
	{
		new[i + j] = file[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

static char	*resolve_path(char *file, char **env)
{
	char	**paths;
	char	*output;
	size_t	i;

	if (!file || !env)
		return (NULL);
	if (access(file, X_OK) >= 0)
		return (ft_strdup(file));
	paths = ft_getenv(env, "PATH");
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		output = join_path(paths[i], file);
		if (access(output, X_OK) >= 0)
			break ;
		free(output);
		output = NULL;
		free(paths[i++]);
	}
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (output);
}

int	ft_get_path(t_cmd *cmd, char **path, t_data	*data)
{
	*path = resolve_path(cmd->cmd_name, data->env);
	if (!(*path) && ft_error('u', cmd) == 1)
	{
		if (cmd->outfile > 1)
			close(cmd->outfile);
		if (cmd->infile > 0)
			close(cmd->infile);
		data->exit_status = 127;
		free(*path);
		return (-1);
	}
	return (1);
}
