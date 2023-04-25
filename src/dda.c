/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:25:16 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 04:31:38 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_camera_ray_direction(t_window *win, int x)
{
	win->ray->camera_x = 2 * x / (double)MAX_WINDOW_WIDTH - 1;
	win->ray->raydir_x = win->dir_x + win->plane_x * win->ray->camera_x;
	win->ray->raydir_y = win->dir_y + win->plane_y * win->ray->camera_x;
}

void	get_map_square(t_window *win)
{
	win->map_x = (int)win->pos_x;
	win->map_y = (int)win->pos_y;
}

void	calculate_deltadist(t_window *win)
{
	win->ray->deltadist_x = DBL_MAX;
	if (win->ray->deltadist_x)
		win->ray->deltadist_x = fabs(1.0 / win->ray->raydir_x);
	win->ray->deltadist_y = DBL_MAX;
	if (win->ray->deltadist_y)
		win->ray->deltadist_y = fabs(1.0 / win->ray->raydir_y);
}

void	calculate_sidedist(t_window *win)
{
	if (win->ray->raydir_x < 0)
	{
		win->ray->step_x = -1;
		win->ray->sidedist_x = (win->pos_x - win->map_x) * \
			win->ray->deltadist_x;
	}
	else
	{
		win->ray->step_x = 1;
		win->ray->sidedist_x = (win->map_x + 1.0 - win->pos_x) * \
			win->ray->deltadist_x;
	}
	if (win->ray->raydir_y < 0)
	{
		win->ray->step_y = -1;
		win->ray->sidedist_y = (win->pos_y - win->map_y) * \
			win->ray->deltadist_y;
	}
	else
	{
		win->ray->step_y = 1;
		win->ray->sidedist_y = (win->map_y + 1.0 - win->pos_y) * \
			win->ray->deltadist_y;
	}
}

void	perform_dda(t_window *win, t_data *map)
{
	win->ray->hit = 0;
	while (win->ray->hit == 0)
	{
		if (win->ray->sidedist_x < win->ray->sidedist_y)
		{
			win->ray->sidedist_x += win->ray->deltadist_x;
			win->map_x += win->ray->step_x;
			win->ray->side = 0;
		}
		else
		{
			win->ray->sidedist_y += win->ray->deltadist_y;
			win->map_y += win->ray->step_y;
			win->ray->side = 1;
		}
		if (win->map_x < 0 || win->map_y < 0 \
			|| win->map_x > MAX_WINDOW_WIDTH || win->map_y > MAX_WINDOW_HEIGHT \
			|| map->maps[win->map_y][win->map_x] == '1')
			win->ray->hit = 1;
	}
}
