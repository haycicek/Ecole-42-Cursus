/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:33:19 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"

int	ft_quote_check(char *input)
{
	int	i;
	int	quote;
	int	dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && dquote == 0)
			quote = !quote;
		if (input[i] == '\"' && quote == 0)
			dquote = !dquote;
		i++;
	}
	if (quote == 1 || dquote == 1)
	{
		printf("Error: quote not closed\n");
		return (0);
	}
	return (1);
}

int	check_strange_chars(t_expand *exped)
{
	if (exped && exped->str && exped->str[0] == '|')
		return ('x');
	while (exped)
	{
		if (exped->str && ft_is_redir(exped->str))
		{
			if (!exped->next)
				return ('r');
		}
		if (exped->str && exped->str[0] == '|')
		{
			if (exped->next && exped->next->str && exped->next->str[0] == '|')
				return ('q');
			if (!exped->next)
				return ('x');
		}
		exped = exped->next;
	}
	return (0);
}

void	free_exp_and_pipe(t_data *data)
{
	free_exp(data->exped);
	free_pipes(data->fd_pipe, data->cmd_cnt);
}

int	is_space(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (1);
		str++;
	}
	return (0);
}
