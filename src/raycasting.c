/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/24 22:53:53 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	start_drawing(t_data *map)
{
	int	i;
	int	j;

	mlx_clear_window(map->mlx, map->mlx_win);
	if (map->img->img)
		mlx_destroy_image(map->mlx, map->img->img);
	map->img->img = mlx_new_image(map->mlx, MAX_WINDOW_WIDTH,
			MAX_WINDOW_HEIGHT);
	map->img->addr = mlx_get_data_addr(map->img->img, &map->img->bpp,
			&map->img->line_length, &map->img->endian);
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

void	update_camera_ray_direction(t_window *win, int x)
{
	win->camera_x = 2 * x / (double)MAX_WINDOW_WIDTH - 1;
	win->raydir_x = win->dir_x + win->plane_x * win->camera_x;
	win->raydir_y = win->dir_y + win->plane_y * win->camera_x;
}

void	get_map_square(t_window *win)
{
	win->map_x = (int)win->pos_x;
	win->map_y = (int)win->pos_y;
}

void	calculate_deltadist_x(t_window *win)
{
	win->deltadist_x = DBL_MAX;
	if (win->deltadist_x)
		win->deltadist_x = fabs(1.0 / win->raydir_x);
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
	win->move_speed = 0.3;
	win->rot_speed = 0.03;
	return (0);
}
