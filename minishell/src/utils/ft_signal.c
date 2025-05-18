/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek/mminga>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:33:00 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/06 02:33:00 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <sys/ioctl.h>
#include "../minishell.h"
#include <unistd.h>

void	sig_int(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	ft_signal(int flag, t_data *data)
{
	if (flag == 1)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == 2)
		ft_exit(""EXIT"Goodbye!"RESET"\n", data);
}
