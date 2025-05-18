/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:34:47 by haycicek          #+#    #+#             */
/*   Updated: 2023/06/16 19:01:41 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_put(int i, int j, t_data *data)
{
	if (data->map[i][j] == '1')
		mlx_put_image_to_window(data->mlx, data->win, data->img.wall,
			j * IMG_SIZE, i * IMG_SIZE);
	else if (data->map[i][j] == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->img.bg,
			j * IMG_SIZE, i * IMG_SIZE);
	else if (data->map[i][j] == 'C')
		mlx_put_image_to_window(data->mlx, data->win, data->img.coin,
			j * IMG_SIZE, i * IMG_SIZE);
	else if (data->map[i][j] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->img.door,
			j * IMG_SIZE, i * IMG_SIZE);
	else if (data->map[i][j] == 'P')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img.character, j * IMG_SIZE, i * IMG_SIZE);
}

static void	map_element_counter(int i, int j, t_data *data)
{
	int	idiot;

	idiot = 0;
	if (data->map[i][j] == '1')
		data->wall_count++;
	else if (data->map[i][j] == '0')
		idiot++;
	else if (data->map[i][j] == 'C')
		data->coin_count++;
	else if (data->map[i][j] == 'E')
	{
		data->exit_count++;
		data->exit_x = j;
		data->exit_y = i;
	}
	else if (data->map[i][j] == 'P')
	{
		data->player_x = j;
		data->player_y = i;
		data->player_count++;
	}
	else
		data->unwanted_character_count++;
}

void	map_create(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			map_element_counter(i, j, data);
			map_put(i, j, data);
			j++;
		}
		i++;
	}
}

void	map_bacgraund_put(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->img.bg,
				j * IMG_SIZE, i * IMG_SIZE);
			j++;
		}
		i++;
	}
}
