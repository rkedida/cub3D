/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/06 17:49:57 by rkedida          ###   ########.fr       */
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
		move_left(map->win);
	else if (keycode == 2)
		move_right(map->win);
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
	// if (map->maps[((int)(win->pos_y + win->dir_y * win->move_speed))][((int)(win->pos_x + win->dir_x * win->move_speed))] != '1')
	// {
	// 	win->pos_x = win->pos_x + win->dir_x * win->move_speed;
	// 	win->pos_y = win->pos_y + win->dir_y * win->move_speed;
	// }
	(void)map;
	printf("-------------------------------------------------------------------------");
	printf("pos = %f,%f\ndir = %f,%f\n", win->pos_x, win->pos_y, win->dir_x, win->dir_y);
	win->pos_x += win->dir_x;
	win->pos_y += win->dir_y;
}

void move_backward(t_data *map, t_window *win)
{
	double new_x = win->pos_x - win->dir_x * win->move_speed;
	double new_y = win->pos_y - win->dir_y * win->move_speed;
	if (map->maps[(int)new_y][(int)new_x] != '1')
	{
		win->pos_x = new_x;
		win->pos_y = new_y;
	}
}

void move_left(t_window *win)
{
	double old_dir_x = win->dir_x;
	win->dir_x = win->dir_x * cos(win->rot_speed) - win->dir_y * sin(win->rot_speed);
	win->dir_y = old_dir_x * sin(win->rot_speed) + win->dir_y * cos(win->rot_speed);
	double old_plane_x = win->plane_x;
	win->plane_x = win->plane_x * cos(win->rot_speed) - win->plane_y * sin(win->rot_speed);
	win->plane_y = old_plane_x * sin(win->rot_speed) + win->plane_y * cos(win->rot_speed);
}

void move_right(t_window *win)
{
	double old_dir_x = win->dir_x;
	win->dir_x = win->dir_x * cos(-win->rot_speed) - win->dir_y * sin(-win->rot_speed);
	win->dir_y = old_dir_x * sin(-win->rot_speed) + win->dir_y * cos(-win->rot_speed);
	double old_plane_x = win->plane_x;
	win->plane_x = win->plane_x * cos(-win->rot_speed) - win->plane_y * sin(-win->rot_speed); 
	win->plane_y = old_plane_x * sin(-win->rot_speed) + win->plane_y * cos(-win->rot_speed);
}
