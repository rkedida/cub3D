/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_wall_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:20:39 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 04:26:14 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_wall_distance(t_window *win)
{
	if (win->ray->side == 0)
		win->ray->perpwalldist = (win->ray->sidedist_x - win->ray->deltadist_x);
	else
		win->ray->perpwalldist = (win->ray->sidedist_y - win->ray->deltadist_y);
}

void	calculate_wall_height(t_window *win)
{
	win->ray->lineheight = (int)(MAX_WINDOW_HEIGHT * 0.6 / \
		win->ray->perpwalldist);
	win->ray->drawstart = -win->ray->lineheight / 2 + MAX_WINDOW_HEIGHT / 2;
	if (win->ray->drawstart < 0)
		win->ray->drawstart = 0;
	win->ray->drawend = win->ray->lineheight / 2 + MAX_WINDOW_HEIGHT / 2;
	if (win->ray->drawend >= MAX_WINDOW_HEIGHT)
		win->ray->drawend = MAX_WINDOW_HEIGHT - 1;
}

void	get_texture_color(t_window *win, t_data *map)
{
	if (win->ray->side == 1 && win->ray->raydir_y < 0)
		map->texture_img = map->texture->north_tex;
	if (win->ray->side == 1 && win->ray->raydir_y > 0)
		map->texture_img = map->texture->south_tex;
	if (win->ray->side == 0 && win->ray->raydir_x > 0)
		map->texture_img = map->texture->east_tex ;
	if (win->ray->side == 0 && win->ray->raydir_x < 0)
		map->texture_img = map->texture->west_tex;
}

void	calculate_wall_x(t_window *win)
{
	if (win->ray->side == 0)
		win->ray->wall_x = win->pos_y + win->ray->perpwalldist * \
			win->ray->raydir_y;
	else
		win->ray->wall_x = win->pos_x + win->ray->perpwalldist * \
			win->ray->raydir_x;
	win->ray->wall_x -= floor((win->ray->wall_x));
}

void	calculate_x_on_texture(t_window *win, t_data *map)
{
	win->ray->tex_x = (int)(win->ray->wall_x * \
			(double)(map->texture_img->img_width));
	if (win->ray->side == 0 && win->ray->raydir_x > 0)
		win->ray->tex_x = map->texture_img->img_width - win->ray->tex_x - 1;
	if (win->ray->side == 1 && win->ray->raydir_y < 0)
		win->ray->tex_x = map->texture_img->img_width - win->ray->tex_x - 1;
	win->ray->step = 1.0 * map->texture_img->img_height / win->ray->lineheight;
	win->tex_pos = (win->ray->drawstart - MAX_WINDOW_HEIGHT / \
		2 + win->ray->lineheight \
					/ 2) * win->ray->step;
}
