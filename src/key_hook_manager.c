/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/23 20:36:01 by rkedida          ###   ########.fr       */
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
		move_left(map->win, map);
	else if (keycode == 2)
		move_right(map->win, map);
	else if (keycode == 123)
		turn_right(map->win);
	else if (keycode == 124)
		turn_left(map->win);
	return (0);
}

void move_forward(t_data *map, t_window *win)
{
	double next_pos_x = win->pos_x + win->dir_x * win->move_speed;
	double next_pos_y = win->pos_y + win->dir_y * win->move_speed;

	if (next_pos_x < 0 || next_pos_y < 0 || next_pos_x > MAX_WINDOW_WIDTH || next_pos_y > MAX_WINDOW_HEIGHT)
		return;

	printf("next_pos forward = %f,%f\n", next_pos_x, next_pos_y);
	if (map->maps[(int)next_pos_y][(int)next_pos_x] != '1')
	{
		win->pos_x = next_pos_x;
		win->pos_y = next_pos_y;
	}
}

void move_backward(t_data *map, t_window *win)
{
	double next_pos_x = win->pos_x - win->dir_x * win->move_speed;
	double next_pos_y = win->pos_y - win->dir_y * win->move_speed;
	
	if (next_pos_x < 0 || next_pos_y < 0 || next_pos_x > MAX_WINDOW_WIDTH || next_pos_y > MAX_WINDOW_HEIGHT)
		return;
	
	printf("next_pos backward = %f,%f\n", next_pos_x, next_pos_y);
	if (map->maps[(int)next_pos_y][(int)next_pos_x] != '1')
	{
		win->pos_x = next_pos_x;
		win->pos_y = next_pos_y;
	}
}

void rotate_vector(double *x, double *y, double theta)
{
	double cos_theta = cosf(theta);
	double sin_theta = sinf(theta);
	double new_x = cos_theta * (*x) - sin_theta * (*y);
	double new_y = sin_theta * (*x) + cos_theta * (*y);
	*x = new_x;
	*y = new_y;
}
void	turn_left(t_window *win)
{
	rotate_vector(&(win->dir_x), &(win->dir_y), -win->rot_speed);
	rotate_vector(&(win->plane_x), &(win->plane_y), -win->rot_speed);
}

void	turn_right(t_window *win)
{
	rotate_vector(&(win->dir_x), &(win->dir_y), win->rot_speed);
	rotate_vector(&(win->plane_x), &(win->plane_y), win->rot_speed);
}

void move_left(t_window *win, t_data *map)
{
	double step_x = win->dir_y * win->move_speed;
	double step_y = -win->dir_x * win->move_speed;
	int new_x = (int)(win->pos_x - step_x);
	int new_y = (int)(win->pos_y - step_y);
	if (map->maps[new_y][new_x] != '1')
	{
		win->pos_x -= step_x;
		win->pos_y -= step_y;
	}
	printf("left_pos = %f,%f\ndir = %f,%f\n", win->pos_x, win->pos_y, win->dir_x, win->dir_y);
}

void move_right(t_window *win, t_data *map)
{
	double step_x = win->dir_y * win->move_speed;
	double step_y = -win->dir_x * win->move_speed;
	int new_x = (int)(win->pos_x + step_x);
	int new_y = (int)(win->pos_y + step_y);
	if (map->maps[new_y][new_x] != '1')
	{
		win->pos_x += step_x;
		win->pos_y += step_y;
	}
	printf("right_pos = %f,%f\ndir = %f,%f\n", win->pos_x, win->pos_y, win->dir_x, win->dir_y);
}