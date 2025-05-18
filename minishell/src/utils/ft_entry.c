/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_entry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek/mminga>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:33:11 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/06 02:33:11 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"

void	ft_entry(void)
{
	printf(CLEAR);
	printf(BOLD BLUE "Welcome to ");
	printf(BOLD GREEN UNDERLINE "mminga & haycicek"RESET);
	printf(BOLD BLUE" minishell!!!\n"RESET);
}
