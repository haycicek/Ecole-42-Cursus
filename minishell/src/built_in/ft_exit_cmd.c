/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:40:14 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../minishell.h"
#include "../../libft/libft.h"

static void	ft_exit_ut(t_cmd *cmd)
{
	int	i;

	if (!(cmd->args[1][0] == '+' || cmd->args[1][0] == '-')
		&& ft_isdigit(cmd->args[1][0]) == 0)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[1]);
		free_cmds(cmd);
		exit(255);
	}
	else if (cmd->args[1][0] == '+' || cmd->args[1][0] == '-')
	{
		i = ft_atoi(cmd->args[1]);
		if (i < 0)
			exit(256 + i);
		else
			exit(i);
	}
	else
	{
		i = ft_atoi(cmd->args[1]);
		free_cmds(cmd);
		exit(i);
	}
}

int	ft_exit_cmd(t_cmd *cmd, int i, t_data *data)
{
	while (cmd->args[i])
		i++;
	if (i == 1)
	{
		free_cmds(cmd);
		free_string(data->prompt);
		free_env(data->environmental);
		free_env(data->export);
		free_array(data->env);
		free_exp(data->exped);
		free_pipes(data->fd_pipe, data->cmd_cnt);
		free(data);
		exit(0);
	}
	else if (i == 2)
		ft_exit_ut(cmd);
	else
	{
		if (ft_isdigit(cmd->args[1][0]) == 1
			&& ft_isalnum(cmd->args[2][0]) == 1)
			return (printf("minishell: exit: too many arguments\n"), 1);
		printf("minishell: exit: numeric argument required\n");
		exit(255);
	}
	return (0);
}
