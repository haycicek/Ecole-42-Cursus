/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:34:22 by haycicek          #+#    #+#             */
/*   Updated: 2023/06/16 19:00:51 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 2, key_hook, data);
	mlx_hook(data->win, 17, 1L << 2, mouse_hook, data);
}

static int	real_walking(int y, int x, t_data *data)
{
	if (data->map[data->player_y + y][data->player_x + x] == '1')
		return (0);
	else if (data->map[data->player_y + y][data->player_x + x] == 'C')
	{
		data->map[data->player_y + y][data->player_x + x] = '0';
		data->coin_collected++;
	}
	else if (data->map[data->player_y + y][data->player_x + x] == 'E')
	{
		exit_door(data);
		return (2);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.door,
		data->exit_x * IMG_SIZE, data->exit_y * IMG_SIZE);
	return (1);
}

static void	step_count(t_data *data)
{
	char	*s;

	data->step_count++;
	ft_printf("Step: %d\r", data->step_count);
	mlx_put_image_to_window(data->mlx, data->win, data->img.wall,
		0 * IMG_SIZE, 0 * IMG_SIZE);
	mlx_put_image_to_window(data->mlx, data->win, data->img.wall,
		1 * IMG_SIZE, 0 * IMG_SIZE);
	mlx_put_image_to_window(data->mlx, data->win, data->img.wall,
		2 * IMG_SIZE, 0 * IMG_SIZE);
	mlx_string_put(data->mlx, data->win, 5, 25,
		0x00FFFFFF, "STEPS: ");
	s = ft_itoa(data->step_count);
	mlx_string_put(data->mlx, data->win, 47, 25,
		0x00FFFFFF, s);
	free(s);
}

static	int	walking(int keycode, t_data *data, int x)
{
	int		val;

	if (keycode == 2 || keycode == 0)
	{
		val = real_walking(0, x, data);
		if (val == 0)
			return (0);
		mlx_put_image_to_window(data->mlx, data->win, data->img.bg,
			data->player_x * IMG_SIZE, data->player_y * IMG_SIZE);
		data->player_x += x;
	}
	if (keycode == 13 || keycode == 1)
	{
		if (real_walking(-x, 0, data) == 0)
			return (0);
		mlx_put_image_to_window(data->mlx, data->win, data->img.bg,
			data->player_x * IMG_SIZE, data->player_y * IMG_SIZE);
		data->player_y -= x;
	}
	step_count(data);
	walking_continue(data);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
		err_msg("Exit Success", data);
	else if (keycode == 2 || keycode == 13)
		walking(keycode, data, 1);
	else if (keycode == 0 || keycode == 1)
		walking(keycode, data, -1);
	return (0);
}
