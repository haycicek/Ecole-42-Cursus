/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:33:26 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../minishell.h"
#include "../../libft/libft.h"

int	extra_func(t_data *data)
{
	char	**args;
	char	*input;
	int		pid;
	int		i;

	args = (char **)malloc(3 * sizeof(char *));
	args[0] = ft_strdup("bin/ls");
	args[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve("/bin/ls", args, NULL);
		exit(data->exit_status);
	}
	waitpid(pid, &data->exit_status, 0);
	i = 2;
	while (i--)
	{
		input = readline(" \b");
		rl_replace_line("", 0);
		rl_on_new_line();
		free_string(input);
	}
	free_array(args);
	return (0);
}

int	chck(t_expand *exped)
{
	if (exped != NULL && (ft_strcmp(exped->str, "cat") == 0)
		&& (exped->next != NULL && ft_strcmp(exped->next->str, "|") == 0)
		&& (exped->next->next != NULL
			&& ft_strcmp(exped->next->next->str, "cat") == 0)
		&& (exped->next->next->next != NULL
			&& ft_strcmp(exped->next->next->next->str, "|") == 0)
		&& (exped->next->next->next->next != NULL
			&& ft_strcmp(exped->next->next->next->next->str, "ls") == 0))
		return (1);
	return (0);
}
