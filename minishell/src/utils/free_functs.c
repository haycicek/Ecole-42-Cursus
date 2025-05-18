/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:26:27 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc/_malloc.h>
#include "../minishell.h"
#include "../../libft/libft.h"

void	free_pipes(int **pipefd, int count)
{
	int	i;

	i = 0;
	if (!pipefd)
		return ;
	while (i < count)
	{
		if (pipefd[i])
		{
			close(pipefd[i][0]);
			close(pipefd[i][1]);
			free(pipefd[i]);
		}
		i++;
	}
	free(pipefd);
}

void	free_string(char *str)
{
	if (str)
		free(str);
}

void	free_array(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		free (str[i]);
	free(str);
	str = NULL;
}

void	free_cmds(t_cmd *cmds)
{
	if (!cmds)
		return ;
	free_string(cmds->cmd_name);
	free_array(cmds->args);
	free(cmds);
}

void	free_exp(t_expand *exped)
{
	t_expand	*tmp;

	if (!exped)
		return ;
	while (exped)
	{
		tmp = exped;
		exped = exped->next;
		free(tmp->str);
		free(tmp);
	}
}
