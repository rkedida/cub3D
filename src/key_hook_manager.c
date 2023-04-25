/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/24 23:19:27 by sheali           ###   ########.fr       */
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
		move_right(map->win, map);
	else if (keycode == 2)
		move_left(map->win, map);
	else if (keycode == 123)
		turn_left(map->win);
	else if (keycode == 124)
		turn_right(map->win);
	printf("keycode: %d\n", keycode);
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

void	turn_right(t_window *win)
{
	rotate_vector(&(win->dir_x), &(win->dir_y), win->rot_speed);
	rotate_vector(&(win->plane_x), &(win->plane_y), win->rot_speed);
}
