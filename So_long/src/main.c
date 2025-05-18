/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:34:30 by haycicek          #+#    #+#             */
/*   Updated: 2023/06/16 19:01:03 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		err_msg("missing or more argument", &data);
	map_control(argv, &data);
	size_control(&data);
	mlx_create(&data);
}
