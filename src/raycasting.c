/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 06:21:21 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	start_drawing(t_data *map)
{
	int	i;
	int	j;

	mlx_clear_window(map->mlx, map->mlx_win);
	if (map->img->img)
		mlx_destroy_image(map->mlx, map->img->img);
	map->img->img = mlx_new_image(map->mlx, MAX_WINDOW_WIDTH, \
		MAX_WINDOW_HEIGHT);
	map->img->addr = mlx_get_data_addr(map->img->img, &map->img->bpp, \
		&map->img->line_length, &map->img->endian);
	key_action(map);
	raycaster(map, map->win);
	draw_buffer(map, map->win->buffer);
	i = 0;
	while (i < MAX_WINDOW_HEIGHT)
	{
		j = 0;
		while (j < MAX_WINDOW_WIDTH)
		{
			map->win->buffer[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

int	raycaster(t_data *map, t_window *win)
{
	int	x;

	x = 0;
	while (x < MAX_WINDOW_WIDTH)
	{
		update_camera_ray_direction(win, x);
		get_map_square(win);
		calculate_deltadist(win);
		calculate_sidedist(win);
		perform_dda(win, map);
		calculate_wall_distance(win);
		calculate_wall_height(win);
		calculate_wall_x(win);
		get_texture_color(win, map);
		calculate_x_on_texture(win, map);
		draw_floor_ceiling(win, map, x);
		draw_vertical_line(win, map, x);
		x++;
	}
	win->move_speed = 0.1;
	win->rot_speed = 0.05;
	return (0);
}
