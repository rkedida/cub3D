/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 06:30:14 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keypress(int keycode, t_data *map)
{
	if (keycode == 53)
		cleanup_and_exit(map);
	else if (keycode == 13)
		map->key.w = 1;
	else if (keycode == 1)
		map->key.s = 1;
	else if (keycode == 0)
		map->key.a = 1;
	else if (keycode == 2)
		map->key.d = 1;
	else if (keycode == 123)
		map->key.left = 1;
	else if (keycode == 124)
		map->key.right = 1;
	return (0);
}

int	handle_keypress_release(int keycode, t_data *map)
{
	if (keycode == 13)
		map->key.w = 0;
	else if (keycode == 1)
		map->key.s = 0;
	else if (keycode == 0)
		map->key.a = 0;
	else if (keycode == 2)
		map->key.d = 0;
	else if (keycode == 123)
		map->key.left = 0;
	else if (keycode == 124)
		map->key.right = 0;
	return (0);
}

int	key_action(t_data *map)
{
	if (map->key.w == 1)
		move_forward(map, map->win);
	if (map->key.s == 1)
		move_backward(map, map->win);
	if (map->key.a == 1)
		move_left(map->win, map);
	if (map->key.d == 1)
		move_right(map->win, map);
	if (map->key.left == 1)
		turn_right(map->win);
	if (map->key.right == 1)
		turn_left(map->win);
	return (0);
}

void	rotate_vector(double *x, double *y, double theta)
{
	double	cos_theta;
	double	sin_theta;
	double	new_x;
	double	new_y;

	cos_theta = cosf(theta);
	sin_theta = sinf(theta);
	new_x = cos_theta * (*x) - sin_theta * (*y);
	new_y = sin_theta * (*x) + cos_theta * (*y);
	*x = new_x;
	*y = new_y;
}

void	turn_left(t_window *win)
{
	rotate_vector(&(win->dir_x), &(win->dir_y), -win->rot_speed);
	rotate_vector(&(win->plane_x), &(win->plane_y), -win->rot_speed);
}
