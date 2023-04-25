/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 00:37:57 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_data *map, t_window *win)
{
	if (map->maps[((int)(win->pos_y + win->dir_y))][((int)(win->pos_x
		+ win->dir_x))] != '1')
	{
		win->pos_x += win->dir_x * win->move_speed;
		win->pos_y += win->dir_y * win->move_speed;
	}
}

void	move_backward(t_data *map, t_window *win)
{
	if (map->maps[((int)(win->pos_y - win->dir_y))][((int)(win->pos_x
		- win->dir_x))] != '1')
	{
		win->pos_x -= win->dir_x * win->move_speed;
		win->pos_y -= win->dir_y * win->move_speed;
	}
}

void	move_left(t_window *win, t_data *map)
{
	double	step_x;
	double	step_y;
	int		new_x;
	int		new_y;

	step_x = win->dir_y * win->move_speed;
	step_y = -win->dir_x * win->move_speed;
	new_x = (int)(win->pos_x - step_x);
	new_y = (int)(win->pos_y - step_y);
	if (map->maps[new_y][new_x] != '1')
	{
		win->pos_x -= step_x;
		win->pos_y -= step_y;
	}
	printf("left_pos = %f,%f\ndir = %f,%f\n", win->pos_x, win->pos_y,
		win->dir_x, win->dir_y);
}

void	move_right(t_window *win, t_data *map)
{
	double	step_x;
	double	step_y;
	int		new_x;
	int		new_y;

	step_x = win->dir_y * win->move_speed;
	step_y = -win->dir_x * win->move_speed;
	new_x = (int)(win->pos_x + step_x);
	new_y = (int)(win->pos_y + step_y);
	if (map->maps[new_y][new_x] != '1')
	{
		win->pos_x += step_x;
		win->pos_y += step_y;
	}
	printf("right_pos = %f,%f\ndir = %f,%f\n", win->pos_x, win->pos_y,
		win->dir_x, win->dir_y);
}
