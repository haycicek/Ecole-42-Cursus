/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek/mminga>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:32:49 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/06 02:32:49 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc/_malloc.h>
#include "../minishell.h"
#include "../../libft/libft.h"

char	*trim_env(char *line, int *k)
{
	int		j;
	char	*env;

	j = 0;
	while (line[j] && line[j] != ' ' && line[j] != '"' && line[j] != '\''
		&& line[j] != '$')
		j++;
	env = (char *)malloc(sizeof(char) * (j + 1));
	j = 0;
	while (line[j] && line[j] != ' ' && line[j] != '"' && line[j] != '\''
		&& line[j] != '$')
	{
		env[j] = line[j];
		j++;
		if (line[0] == '?')
			break ;
	}
	env[j] = '\0';
	*k += j;
	return (env);
}

void	ft_add_back(t_env *new, t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	if (!(*head))
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_env	*ft_new_list(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

static int	ft_index_of_equal_sign(char *str)
{
	int	counter;

	counter = 0;
	while (*(str + counter))
	{
		if (*(str + counter) == '=')
			return (counter);
		counter++;
	}
	return (-1);
}

void	ft_load(char **env, int choose, t_data *data)
{
	t_env	*tmp;
	int		len;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		tmp = ft_new_list();
		if (!tmp)
			return ;
		flag = ft_index_of_equal_sign(env[i]);
		if (flag == -1)
			ft_exit("Error: no equal sign in env variable.\n", data);
		tmp->key = ft_substr(env[i], 0, flag);
		tmp->value = ft_substr(env[i], flag + 1, len);
		if (choose == 0)
			ft_add_back(tmp, &data->environmental);
		else
			ft_add_back(tmp, &data->export);
		i++;
	}
}
