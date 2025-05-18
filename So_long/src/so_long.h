/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:35:05 by haycicek          #+#    #+#             */
/*   Updated: 2023/06/16 19:02:27 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define IMG_SIZE 50

typedef struct l_image
{
	char	*character;
	char	*wall;
	char	*coin;
	char	*door_open;
	char	*bg;
	char	*door;
	int		img_w;
	int		img_h;
}			t_image;
/*
	l = left
	r = right
	t = top
	b = bottom
*/
typedef struct l_int_map
{
	int		l;
	int		r;
	int		t;
	int		b;
	int		read_count;
	int		step_count;
}			t_int_map;

typedef struct l_data
{
	char		**map;
	char		*mlx;
	char		*win;
	char		*map_tmp;
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	int			player_count;
	int			exit_count;
	int			exit_x;
	int			exit_y;
	int			wall_count;
	int			coin_count;
	int			unwanted_character_count;
	int			coin_collected;
	int			step_count;
	t_image		img;
	t_int_map	i_map;
}				t_data;

void		mlx_create(t_data *data);
void		map_control(char **argv, t_data *data);
void		ber_control(char *map_name, t_data *data);
void		tmp_control(char *map_name, t_data *data);
void		map_read(t_data *data);
void		map_create(t_data *data);
void		size_control(t_data *data);
void		*myfree(void *str);
char		*get_next_line(int fd);
void		err_msg(char *msg, t_data *g);
void		hook(t_data *data);
int			key_hook(int keycode, t_data *data);
int			mouse_hook(int mousecode, t_data *data);
void		exit_door(t_data *data);
void		map_bacgraund_put(t_data *data);
void		map_put(int i, int j, t_data *data);
void		min_element_control(t_data *data);
void		placeholder(t_data *list, int x, int y);
void		wall_control(t_data *data);
void		walking_continue(t_data *data);

#endif
