/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/24 19:34:48 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	move_forward(t_data *map, t_window *win)
// {
// 	if (map->maps[((int)(win->pos_y + win->dir_y))][((int)(win->pos_x
// 		+ win->dir_x))] != '1')
// 	{
// 		win->pos_x += win->dir_x;
// 		win->pos_y += win->dir_y;
// 	}
// }

void	move_backward(t_data *map, t_window *win)
{
	if (map->maps[((int)(win->pos_y - win->dir_y))][((int)(win->pos_x
		- win->dir_x))] != '1')
	{
		win->pos_x -= win->dir_x;
		win->pos_y -= win->dir_y;
	}
}

void	move_left(t_window *win, t_data *map)
{
	(void)map;
	rotate_vector(&(win->dir_x), &(win->dir_y), win->rot_speed);
	rotate_vector(&(win->plane_x), &(win->plane_y), win->rot_speed);
	printf("pos = %f,%f\ndir = %f,%f\n", win->pos_x, win->pos_y,
		win->dir_x, win->dir_y);
}

void	move_right(t_window *win, t_data *map)
{
	(void)map;
	rotate_vector(&(win->dir_x), &(win->dir_y), -win->rot_speed);
	rotate_vector(&(win->plane_x), &(win->plane_y), -win->rot_speed);
	printf("pos = %f,%f\ndir = %f,%f\n", win->pos_x, win->pos_y,
		win->dir_x, win->dir_y);
}

void	move_forward(t_data *map, t_window *win)
{
	double new_x = win->pos_x + win->dir_x;
	double new_y = win->pos_y + win->dir_y;

	if (map->maps[(int)new_y][(int)new_x] != '1')
	{
		win->pos_x = new_x;
		win->pos_y = new_y;
	}
	else
	{
		double dist_x = new_x - (int)new_x;
		double dist_y = new_y - (int)new_y;
		if (dist_x < 0.1)
			win->pos_x = (int)new_x;
		if (dist_x > 0.9)
			win->pos_x = (int)new_x + 1;
		if (dist_y < 0.1)
			win->pos_y = (int)new_y;
		if (dist_y > 0.9)
			win->pos_y = (int)new_y + 1;
	}
}
