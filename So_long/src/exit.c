/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:34:08 by haycicek          #+#    #+#             */
/*   Updated: 2023/06/16 19:00:02 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	err_msg(char *msg, t_data *g)
{
	ft_printf("%s", msg);
	exit(0);
}

int	mouse_hook(int mousecode, t_data *data)
{
	err_msg("Exit Success", data);
	return (0);
}

void	walking_continue(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img.bg,
		data->player_x * IMG_SIZE, data->player_y * IMG_SIZE);
	mlx_put_image_to_window(data->mlx, data->win, data->img.door,
		data->exit_x * IMG_SIZE, data->exit_y * IMG_SIZE);
	if (data->coin_collected == data->coin_count)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img.door_open,
			data->exit_x * IMG_SIZE, data->exit_y * IMG_SIZE);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.character,
		data->player_x * IMG_SIZE, data->player_y * IMG_SIZE);
}

void	exit_door(t_data *data)
{
	if (data->coin_collected == data->coin_count)
	{	
		err_msg("FINISH", data);
	}
	else
		ft_printf("Sorry, you can't exit.\n");
}
