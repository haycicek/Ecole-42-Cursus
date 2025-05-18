/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:10:38 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include "../minishell.h"
#include "../../libft/libft.h"

int	g_sin = 0;

static void	write_to_file(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static void	sig_handler(int sig)
{
	(void)sig;
	g_sin = 42;
}

static void	ft_signal_heredoc(void)
{
	signal(SIGINT, sig_handler);
	if (g_sin == 42)
		exit(1);
}

void	ft_get_heredoc_lines(char *delim, int fd, t_data *data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_signal_heredoc();
		line = readline(">");
		if (line)
		{
			if (!ft_strcmp(line, delim))
				break ;
			else
				write_to_file(line, fd);
			free_string(line);
		}
		else
			ft_signal(2, data);
	}
	free_string(line);
	close(fd);
}

void	handle_heredoc_file(t_cmd *cmd, char *delim, t_data *data)
{
	int	pid;

	pipe(data->fd_heredoc);
	cmd->infile = data->fd_heredoc[0];
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		close(data->fd_heredoc[0]);
		ft_get_heredoc_lines(delim, data->fd_heredoc[1], data);
		exit(0);
	}
	else
	{
		close(data->fd_heredoc[1]);
		waitpid(pid, &data->exit_status, 0);
		data->exit_status = data->exit_status / 256;
	}
}
