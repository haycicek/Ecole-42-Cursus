/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:48:47 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"
#include "../../libft/libft.h"

static int	ft_is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

static void	ft_dup_fds(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (cmd->infile > 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile > 1)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	while (i < data->cmd_cnt)
	{
		close(data->fd_pipe[i][0]);
		close(data->fd_pipe[i][1]);
		i++;
	}
}

static void	ft_execute_builtin(t_cmd *cmd, int tmp_in, int tmp_out,
		t_data *data)
{
	tmp_in = dup(0);
	tmp_out = dup(1);
	ft_dup_fds(cmd, data);
	if (ft_strcmp(cmd->cmd_name, "echo") == 0)
		data->exit_status = ft_echo(cmd);
	if (ft_strcmp(cmd->cmd_name, "cd") == 0)
		data->exit_status = ft_cd(cmd, data);
	if (ft_strcmp(cmd->cmd_name, "pwd") == 0)
		data->exit_status = ft_pwd();
	if (ft_strcmp(cmd->cmd_name, "export") == 0)
		data->exit_status = ft_export(cmd, data);
	if (ft_strcmp(cmd->cmd_name, "unset") == 0)
		data->exit_status = ft_unset(cmd, data);
	if (ft_strcmp(cmd->cmd_name, "env") == 0)
		data->exit_status = ft_env(data);
	if (ft_strcmp(cmd->cmd_name, "exit") == 0)
	{
		ft_putstr_fd("exit\n", 1);
		if (ft_exit_cmd(cmd, 0, data))
			data->exit_status = 1;
	}
	dup2(tmp_in, 0);
	dup2(tmp_out, 1);
	close(tmp_in);
	close(tmp_out);
}

static int	ft_handle_builtin(t_cmd *cmd, t_data *data)
{
	int	pid;
	int	tmp_in;
	int	tmp_out;

	tmp_in = 0;
	tmp_out = 1;
	if (data->cmd_cnt > 1)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_execute_builtin(cmd, tmp_in, tmp_out, data);
			exit(127);
		}
		if (cmd->outfile > 1)
			close(cmd->outfile);
		if (cmd->infile > 0)
			close(cmd->infile);
		waitpid(pid, &data->exit_status, 0);
	}
	else
		ft_execute_builtin(cmd, tmp_in, tmp_out, data);
	return (1);
}

int	exec_ft(t_cmd *cmd, int i, t_data *data)
{
	char	*path;
	int		pid;

	if (ft_is_built_in(cmd->cmd_name))
		return (ft_handle_builtin(cmd, data));
	if (ft_get_path(cmd, &path, data) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		ft_dup_fds(cmd, data);
		execve(path, cmd->args, data->env);
		ft_error('d', cmd);
		exit(data->exit_status);
	}
	if (cmd->outfile > 1)
		close(cmd->outfile);
	if (cmd->infile > 0)
		close(cmd->infile);
	if (i > 0)
		close(data->fd_pipe[i - 1][1]);
	waitpid(pid, &data->exit_status, 0);
	data->exit_status /= 256;
	free(path);
	return (1);
}
