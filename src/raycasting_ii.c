/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_ii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/21 00:28:16 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_deltadist_y(t_window *win)
{
	win->deltadist_y = DBL_MAX;
	if (win->deltadist_y)
		win->deltadist_y = fabs(1.0 / win->raydir_y);
}

void	calculate_deltadist(t_window *win)
{
	calculate_deltadist_x(win);
	calculate_deltadist_y(win);
	if (win->raydir_x < 0)
	{
		win->step_x = -1;
		win->sidedist_x = (win->pos_x - win->map_x) * win->deltadist_x;
	}
	else
	{
		win->step_x = 1;
		win->sidedist_x = (win->map_x + 1.0 - win->pos_x) * win->deltadist_x;
	}
	if (win->raydir_y < 0)
	{
		win->step_y = -1;
		win->sidedist_y = (win->pos_y - win->map_y) * win->deltadist_y;
	}
	else
	{
		win->step_y = 1;
		win->sidedist_y = (win->map_y + 1.0 - win->pos_y) * win->deltadist_y;
	}
}

void	perform_dda(t_window *win, t_data *map)
{
	// perform DDA
	win->hit = 0;
	while (win->hit == 0)
	{
		// jump to next map square, or in x-direction, or in y-direction
		if (win->sidedist_x < win->sidedist_y)
		{
			win->sidedist_x += win->deltadist_x;
			win->map_x += win->step_x;
			win->side = 0;
		}
		else
		{
			win->sidedist_y += win->deltadist_y;
			win->map_y += win->step_y;
			win->side = 1;
		}
		if (map->map[win->map_y][win->map_x] == '1')
			win->hit = 1;
	}
}

void	calculate_wall_distance(t_window *win)
{
	// Calculate distance of perpendicular ray (Euclidean distance would
	// give fisheye effect)
	if (win->side == 0)
		win->perpwalldist = (win->sidedist_x - win->deltadist_x);
	else
		win->perpwalldist = (win->sidedist_y - win->deltadist_y);
}

void	calculate_wall_height(t_window *win)
{
	// Calculate height of line to draw on screen
	win->lineheight = (int)(MAX_WINDOW_HEIGHT * 0.6 / win->perpwalldist);
	// Calculate lowest and highest pixel to fill in current stripe
	//printf("lineheight = %d, MAX_WINDOW_HEIGHT = %d\n", win->lineheight,
	// MAX_WINDOW_HEIGHT);
	win->drawstart = -win->lineheight / 2 + MAX_WINDOW_HEIGHT / 2;
	if (win->drawstart < 0)
		win->drawstart = 0;
	win->drawend = win->lineheight / 2 + MAX_WINDOW_HEIGHT / 2;
	if (win->drawend >= MAX_WINDOW_HEIGHT)
		win->drawend = MAX_WINDOW_HEIGHT - 1;
}
