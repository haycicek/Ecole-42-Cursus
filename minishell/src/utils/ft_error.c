/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:26:19 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:31:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"
#include "../../libft/libft.h"

int	ft_error(char type, t_cmd *cmd)
{
	printf("minishell: ");
	if (type == 'm')
		printf("Memory allocation failed\n");
	else if (type == ';' || type == 's')
		printf("I cant handle ';' or ';;'\n");
	else if (type == '\\')
		printf("I cant handle '\\'\n");
	else if (type == 'r')
		printf("No file after redirection\n");
	else if (type == 'u')
		printf("%s: command not found\n", cmd->cmd_name);
	else if (type == 'p')
		printf(" pipe open error\n");
	else if (type == 'q')
		printf("I cant handle '||'\n");
	else if (type == 'x')
		printf("no command after pipe\n");
	else if (type == 'e')
		printf("export: `%s': not a valid identifier\n", cmd->args[1]);
	else if (type == 'd')
	{
		printf("%s: is a directory\n", cmd->cmd_name);
		free_cmds(cmd);
	}
	return (1);
}

int	ft_control(char *input)
{
	if ((input[0] == '\"' && input[1] == '\"')
		|| (input[0] == '\'' && input[1] == '\''))
	{
		printf("minishell: ");
		printf(": command not found\n");
		return (0);
	}
	if (ft_strchr(input, ';') != (char *)0)
		return (ft_error(';', 0), 0);
	if (ft_strchr(input, '\\') != (char *)0)
		return (ft_error('\\', 0), 0);
	return (1);
}
