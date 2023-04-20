/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_iii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/21 00:51:14 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_texture_color(t_window *win, t_data *map)
{
	if (win->side == 0 && win->raydir_x > 0)
		map->texture_img = map->texture->north_tex;
	if (win->side == 0 && win->raydir_x < 0)
		map->texture_img = map->texture->south_tex;
	if (win->side == 1 && win->raydir_y < 0)
		map->texture_img = map->texture->west_tex;
	if (win->side == 1 && win->raydir_y > 0)
		map->texture_img = map->texture->east_tex;
}

void	calculate_wall_x(t_window *win)
{
	// calculate value of wall_x
	if (win->side == 0)
		win->wall_x = win->pos_y + win->perpwalldist * win->raydir_y;
	else
		win->wall_x = win->pos_x + win->perpwalldist * win->raydir_x;
	win->wall_x -= floor((win->wall_x));
}

void	calculate_x_on_texture(t_window *win, t_data *map)
{
	// x coordinate on the texture
	(void)map;
	win->tex_x = (int)(win->wall_x * (double)(map->texture_img->img_width));
	if (win->side == 0 && win->raydir_x > 0)
		win->tex_x = map->texture_img->img_width - win->tex_x - 1;
	if (win->side == 1 && win->raydir_y < 0)
		win->tex_x = map->texture_img->img_width - win->tex_x - 1;
	// how much to increase the texture coordinate per screen pixel
	win->step = 1.0 * map->texture_img->img_height / win->lineheight;
	// starting texture coordinate
	win->tex_pos = (win->drawstart - MAX_WINDOW_HEIGHT / 2
			+ win->lineheight / 2) * win->step;
}

void	draw_floor_ceiling(t_window *win, t_data *map, int x)
{
	int	y;

	y = 0;
	// Set floor and ceiling colors in buffer
	while (y < win->drawstart)
	{
		win->buffer[y][x] = (unsigned int)RGB(map->color->ceiling_r,
				map->color->ceiling_g, map->color->ceiling_b, 125);
		y++;
	}
	y = win->drawend;
	while (y < MAX_WINDOW_HEIGHT)
	{
		win->buffer[y][x] = (unsigned int)RGB(map->color->floor_r,
				map->color->floor_g, map->color->floor_b, 125);
		y++;
	}
}

void	draw_vertical_line(t_window *win, t_data *map, int x)
{
	int	y;

	y = win->drawstart;
	while (y < win->drawend)
	{
		// cast the texture coordinate to integer, and mask with
		// (tex_height - 1) in case of overflow
		win->tex_y = (int)win->tex_pos & (map->texture_img->img_height - 1);
		//printf("tex_x : %d, tex_y : %d\n", win->tex_x, win->tex_y);
		win->tex_pos += win->step;
		map->color->color = get_tex_pixel(map->texture_img, win->tex_x,
				win->tex_y);
		if (win->side == 1)
			map->color->color = (map->color->color >> 1) & 8355711;
		win->buffer[y][x]= map->color->color;
		y++;
	}
}

//-------------------------------TEST--------------------------------------

void	ft_mlx_pixel_put(t_img *texture, int x, int y, int color)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_buffer(t_data *map,
	uint32_t buffer[MAX_WINDOW_HEIGHT][MAX_WINDOW_WIDTH])
{
	int	x;
	int	y;

	y = 0;
	while (y < MAX_WINDOW_HEIGHT)
	{
		x = 0;
		while (x < MAX_WINDOW_WIDTH)
		{
			ft_mlx_pixel_put(map->img, x, y, buffer[y][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img->img, 0, 0);
}

int	get_tex_pixel(t_img *texture, int x, int y)
{
	int				color;
	char			*dst;

	color = 0;
	dst = NULL;
	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
