/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cmd_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:10:46 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/10 00:44:05 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../minishell.h"

void	ft_redir_error(t_cmd *cmd, char *str, char *filename)
{
	printf("minishell: %s: No such file or directory\n", str);
	if (filename)
		free(filename);
	if (!cmd)
		free_cmds(cmd);
}
