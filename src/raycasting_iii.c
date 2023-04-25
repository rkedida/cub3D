/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_iii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 00:32:34 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_texture_color(t_window *win, t_data *map)
{
	if (win->side == 1 && win->raydir_y < 0)
		map->texture_img = map->texture->north_tex;
	if (win->side == 1 && win->raydir_y > 0)
		map->texture_img = map->texture->south_tex;
	if (win->side == 0 && win->raydir_x > 0)
		map->texture_img = map->texture->east_tex;
	if (win->side == 0 && win->raydir_x < 0)
		map->texture_img = map->texture->west_tex;
}

void	calculate_wall_x(t_window *win)
{
	if (win->side == 0)
		win->wall_x = win->pos_y + win->perpwalldist * win->raydir_y;
	else
		win->wall_x = win->pos_x + win->perpwalldist * win->raydir_x;
	win->wall_x -= floor((win->wall_x));
}

void	calculate_x_on_texture(t_window *win, t_data *map)
{
	(void)map;
	win->tex_x = (int)(win->wall_x * (double)(map->texture_img->img_width));
	if (win->side == 0 && win->raydir_x > 0)
		win->tex_x = map->texture_img->img_width - win->tex_x - 1;
	if (win->side == 1 && win->raydir_y < 0)
		win->tex_x = map->texture_img->img_width - win->tex_x - 1;
	win->step = 1.0 * map->texture_img->img_height / win->lineheight;
	win->tex_pos = (win->drawstart - MAX_WINDOW_HEIGHT / 2
			+ win->lineheight / 2) * win->step;
}

void	draw_floor_ceiling(t_window *win, t_data *map, int x)
{
	int	y;

	y = 0;
	if (!(win && win->drawstart && win->drawend))
		return ;
	else
	{
		while (y < win->drawstart)
		{
			if (map && map->color)
				win->buffer[y][x] = (unsigned int)rgb(map->color->ceiling_r,
						map->color->ceiling_g, map->color->ceiling_b, 125);
			y++;
		}
		y = win->drawend;
		while (y < MAX_WINDOW_HEIGHT)
		{
			if (map && map->color)
				win->buffer[y][x] = (unsigned int)rgb(map->color->floor_r,
						map->color->floor_g, map->color->floor_b, 125);
			y++;
		}
	}
}

void	draw_vertical_line(t_window *win, t_data *map, int x)
{
	int	y;

	y = win->drawstart;
	while (y < win->drawend)
	{
		win->tex_y = (int)win->tex_pos & (map->texture_img->img_height - 1);
		win->tex_pos += win->step;
		map->color->color = get_tex_pixel(map->texture_img, win->tex_x,
				win->tex_y);
		if (win->side == 1)
			map->color->color = (map->color->color >> 1) & 8355711;
		win->buffer[y][x] = map->color->color;
		y++;
	}
}
