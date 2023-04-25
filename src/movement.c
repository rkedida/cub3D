/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:32:32 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 18:12:06 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_data *map, t_window *win)
{
	double	next_pos_x;
	double	next_pos_y;

	next_pos_x = win->pos_x + win->dir_x * win->move_speed;
	next_pos_y = win->pos_y + win->dir_y * win->move_speed;
	if (next_pos_x < 0 || next_pos_y < 0 || next_pos_x > MAX_WINDOW_WIDTH \
			|| next_pos_y > MAX_WINDOW_HEIGHT)
		return ;
	if (map->maps[(int)next_pos_y][(int)next_pos_x] != '1')
	{
		win->pos_x = next_pos_x;
		win->pos_y = next_pos_y;
	}
}

void	move_backward(t_data *map, t_window *win)
{
	double	next_pos_x;
	double	next_pos_y;

	next_pos_x = win->pos_x - win->dir_x * win->move_speed;
	next_pos_y = win->pos_y - win->dir_y * win->move_speed;
	if (next_pos_x < 0 || next_pos_y < 0 || next_pos_x > MAX_WINDOW_WIDTH \
			|| next_pos_y > MAX_WINDOW_HEIGHT)
		return ;
	if (map->maps[(int)next_pos_y][(int)next_pos_x] != '1')
	{
		win->pos_x = next_pos_x;
		win->pos_y = next_pos_y;
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
	if (new_x < 0 || new_y < 0 || new_x > MAX_WINDOW_WIDTH || new_y > \
			MAX_WINDOW_HEIGHT)
		return ;
	if (map->maps[new_y][new_x] != '1')
	{
		win->pos_x -= step_x;
		win->pos_y -= step_y;
	}
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
	if (new_x < 0 || new_y < 0 || new_x > MAX_WINDOW_WIDTH || new_y > \
			MAX_WINDOW_HEIGHT)
		return ;
	if (map->maps[new_y][new_x] != '1')
	{
		win->pos_x += step_x;
		win->pos_y += step_y;
	}
}
