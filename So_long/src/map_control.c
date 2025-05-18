/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:34:35 by haycicek          #+#    #+#             */
/*   Updated: 2023/06/16 19:01:20 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ber_control(char *map_name, t_data *data)
{
	int	arg_len;

	arg_len = ft_strlen(map_name);
	if (map_name[arg_len - 1] != 'r' || map_name[arg_len - 2] != 'e'
		|| map_name[arg_len - 3] != 'b' || map_name[arg_len - 4] != '.')
		err_msg("Error\n-->Map file is not .ber", data);
}

void	tmp_control(char *map_name, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(ft_strjoin("map/", map_name), O_RDONLY);
	if (fd == -1)
		err_msg("Error\n-->Map file is not found...", data);
	line = get_next_line(fd);
	if (!line || !line[0])
		err_msg("Error\n-->Map is Empty", data);
	close(fd);
	free(line);
	if (!map_name)
		free(map_name);
}

void	map_control(char **argv, t_data *data)
{
	char	*map_name;
	char	*map_names;

	if (argv[1] == 0)
		err_msg("Error\n-->No map file", data);
	map_name = argv[1];
	map_names = ft_strjoin("map/", map_name);
	data->map_tmp = map_names;
	free(map_names);
	ber_control(argv[1], data);
	tmp_control(argv[1], data);
}
