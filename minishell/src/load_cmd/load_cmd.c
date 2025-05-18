/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:11:20 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:44:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "../minishell.h"
#include "../../libft/libft.h"

static int	handle_pipe(t_cmd *cmd, int idx, t_data *data)
{
	if ((idx != 0 && idx < data->cmd_cnt - 1))
	{
		if (cmd->infile == 0)
			cmd->infile = data->fd_pipe[idx - 1][0];
		if (cmd->outfile == 1)
			cmd->outfile = data->fd_pipe[idx][1];
	}
	else if (idx == 0 && idx < data->cmd_cnt - 1 && cmd->outfile == 1)
		cmd->outfile = data->fd_pipe[idx][1];
	else if (idx != 0 && idx == data->cmd_cnt - 1)
	{
		if (cmd->infile == 0)
			cmd->infile = data->fd_pipe[idx - 1][0];
		if (cmd->outfile == 1)
			cmd->outfile = 1;
	}
	return (1);
}

int	handle_redir(t_cmd *cmd, t_expand **exped, t_data *data)
{
	char	*filename;

	filename = ft_trim_quotes((*exped)->next->str, 0, 0);
	if (!(*exped) || !(*exped)->str || !(*exped)->next || !(*exped)->next->str)
		return (-1);
	if ((*exped)->str[0] == '>' && (*exped)->str[1] == '>')
		cmd->outfile = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if ((*exped)->str[0] == '<' && (*exped)->str[1] == '<')
		handle_heredoc_file(cmd, filename, data);
	else if ((*exped)->str[0] == '>')
		cmd->outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if ((*exped)->str[0] == '<')
		cmd->infile = open(filename, O_RDONLY);
	if (cmd->infile == -1 || cmd->outfile == -1)
	{
		ft_redir_error(cmd, (*exped)->next->str, filename);
		data->exit_status = 1;
		return (-1);
	}
	*exped = (*exped)->next->next;
	free(filename);
	return (1);
}

int	ft_get_cmd(t_expand **exped, t_cmd *tmp, int indx, t_data *data)
{
	while (*exped && !ft_is_pipe((*exped)->str))
	{
		if (ft_is_redir((*exped)->str))
		{
			if (handle_redir(tmp, exped, data) == -1)
				return (-1);
		}
		else if (!(tmp->cmd_name))
		{
			tmp->cmd_name = ft_trim_quotes((*exped)->str, 0, 0);
			tmp->args = ft_load_args(exped, tmp, ft_arg_size(*exped), data);
			if (!(tmp->args))
				return (-1);
			handle_pipe(tmp, indx, data);
		}
		else
			*exped = (*exped)->next;
	}
	if (*exped)
		*exped = (*exped)->next;
	return (1);
}

static int	init_pipe(int count, t_data *data)
{
	int	**pipefd;
	int	i;

	i = 0;
	data->cmd_cnt = count + 1;
	pipefd = (int **)malloc(sizeof(int *) * (count + 1));
	if (!pipefd)
		return (-1);
	while (i < count + 1)
	{
		pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!(pipefd[i]))
			return (-1);
		if (pipe(pipefd[i]) == -1)
		{
			ft_error('p', NULL);
			return (-1);
		}
		i++;
	}
	data->fd_pipe = pipefd;
	return (0);
}

int	load_cmd(t_expand *exped, t_data *data, int count, int i)
{
	t_cmd	*tmp;

	count = ft_count_pipe(exped);
	if (count == -1)
		return (-2);
	init_pipe(count, data);
	if (chck(data->exped))
		return (extra_func(data), 2);
	while (exped)
	{
		tmp = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
		if (!tmp)
			return (-1);
		tmp->outfile = 1;
		if (ft_get_cmd(&exped, tmp, i, data) == -1)
			return (free_cmds(tmp), -1);
		if (tmp->cmd_name != 0 && *(tmp->cmd_name) != '\0')
			exec_ft(tmp, i, data);
		wait(NULL);
		free_cmds(tmp);
		tmp = NULL;
		i++;
	}
	return (ft_signal(1, data), 0);
}
