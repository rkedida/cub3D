/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/10 17:15:29 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keypress(int keycode, t_data *map)
{
	if (keycode == 53)
		cleanup_and_exit(map);
	else if (keycode == 13)
		move_forward(map, map->win);
	else if (keycode == 1)
		move_backward(map, map->win);
	else if (keycode == 0)
		move_right(map->win);
	else if (keycode == 2)
		move_left(map->win);
	// if (Map->max_collectibles == 0)
	// {
	// 	Map->map[Map->exit_pos[0]][Map->exit_pos[1]] = 'E';
	// 	load_texture('E', Map->exit_pos[0], Map->exit_pos[1], Map->img);
	// }
	if (keycode == 53 || keycode == 13 || keycode ==1 || keycode == 0 || keycode == 2)
		start_drawing(map);
	return (0);
}

void move_forward(t_data *map, t_window *win)
{
	// double new_x = win->pos_x + win->dir_x * win->move_speed;
	// double new_y = win->pos_y + win->dir_y * win->move_speed;
	// 	win->pos_x = win->pos_x + win->dir_x * win->move_speed;
	// 	win->pos_y = win->pos_y + win->dir_y * win->move_speed;
	(void)map;
	printf("-------------------------------------------------------------------------");
	printf("pos = %f,%f\ndir = %f,%f\n", win->pos_x, win->pos_y, win->dir_x, win->dir_y);
	if (map->maps[((int)(win->pos_y + win->dir_y))][((int)(win->pos_x + win->dir_x))] != '1')
	{
		win->pos_x += win->dir_x;
		win->pos_y += win->dir_y;
	}
}

void move_backward(t_data *map, t_window *win)
{
	// double new_x = win->pos_x - win->dir_x;
	// double new_y = win->pos_y - win->dir_y;
	if (map->maps[((int)(win->pos_y - win->dir_y))][((int)(win->pos_x - win->dir_x))] != '1')
	{
		win->pos_x -= win->dir_x;
		win->pos_y -= win->dir_y;
	}
}

void rotate_vector(double *x, double *y, double theta)
{
    double cos_theta = cos(theta);
    double sin_theta = sin(theta);
    double new_x = cos_theta * (*x) - sin_theta * (*y);
    double new_y = sin_theta * (*x) + cos_theta * (*y);
    *x = new_x;
    *y = new_y;
}

void move_left(t_window *win)
{
    rotate_vector(&(win->dir_x), &(win->dir_y), win->rot_speed);
    rotate_vector(&(win->plane_x), &(win->plane_y), win->rot_speed);
	printf("pos = %f,%f\ndir = %f,%f\n", win->pos_x, win->pos_y, win->dir_x, win->dir_y);
}

void move_right(t_window *win)
{
    rotate_vector(&(win->dir_x), &(win->dir_y), -win->rot_speed);
    rotate_vector(&(win->plane_x), &(win->plane_y), -win->rot_speed);
	printf("pos = %f,%f\ndir = %f,%f\n", win->pos_x, win->pos_y, win->dir_x, win->dir_y);
}
