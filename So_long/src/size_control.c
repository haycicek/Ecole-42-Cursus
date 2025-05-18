/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:34:58 by haycicek          #+#    #+#             */
/*   Updated: 2023/06/16 19:02:14 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	size_control(t_data *data)
{
	int		fd;
	char	*line;
	int		y;
	int		x;

	y = 0;
	fd = open(data->map_tmp, O_RDONLY);
	line = get_next_line(fd);
	x = ft_strlen(line);
	while (1)
	{
		free(line);
		y++;
		line = get_next_line(fd);
		if (line[0] == '\0')
			break ;
		if (x != ft_strlen(line) && line[0] != '\0')
			err_msg("Error\n-->Map is not rectangular", data);
	}
	if (!line)
		free(line);
	data->map_height = y;
	data->map_width = x - 1;
	close (fd);
}

void	wall_control(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < data->map_width)
		if (data->map[0][x++] != '1')
			err_msg("Error\n-->1The map has to be surrounded by walls", data);
	while (y < data->map_height)
	{
		if (data->map[y][0] != '1' || data->map[y][data->map_width - 1] != '1')
			err_msg("Error\n-->yanThe map has to be surrounded by walls", data);
		y++;
	}
	x = 0;
	while (x < data->map_width)
		if (data->map[data->map_height - 1][x++] != '1')
			err_msg("Error\n-->sonThe map has to be surrounded by walls", data);
}

void	min_element_control(t_data *data)
{
	if (data->player_count != 1)
		err_msg("Error\n-->There must be 1 player on the map", data);
	if (data->exit_count != 1)
		err_msg("Error\n-->There must be 1 exit on the map", data);
	if (data->coin_count < 1)
		err_msg("Error\n-->Must have at least 1 collectible on the map", data);
	if (data->wall_count < 9)
		err_msg("Error\n-->Wrong on the map", data);
	if (data->unwanted_character_count != 0)
		err_msg("Error\n--> Only [0,1,E,P,C] characters", data);
}
