/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 02:57:33 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 21:23:10 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_ceiling(t_window *win, t_data *map, int x)
{
	int	y;

	y = 0;
	if (win && win->ray->drawend && win->ray->drawstart)
	{
		while (y < win->ray->drawstart)
		{
			if (map && map->color)
			{
				win->buffer[y][x] = (unsigned int)rgb(map->color->ceiling_r, \
							map->color->ceiling_g, map->color->ceiling_b, 125);
				y++;
			}
		}
		y = win->ray->drawend;
		while (y < MAX_WINDOW_HEIGHT)
		{
			if (map && map->color)
			{
				win->buffer[y][x] = (unsigned int)rgb(map->color->floor_r, \
								map->color->floor_g, map->color->floor_b, 125);
				y++;
			}
		}
	}
}

int	get_tex_pixel(t_img *texture, int x, int y)
{
	unsigned int	color;
	char			*dst;

	color = 0;
	dst = NULL;
	if (texture != NULL && texture->addr != NULL && x >= 0 \
		&& x < texture->img_width && y >= 0 && y < texture->img_height)
	{
		dst = texture->addr + (y * texture->line_length + x * \
							(texture->bpp / 8));
		color = *(unsigned int *)dst;
	}
	return (color);
}

void	draw_vertical_line(t_window *win, t_data *map, int x)
{
	int	y;

	y = win->ray->drawstart;
	while (y < win->ray->drawend)
	{
		win->ray->tex_y = (int)win->tex_pos & \
			(map->texture_img->img_height - 1);
		win->tex_pos += win->ray->step;
		map->color->color = get_tex_pixel(map->texture_img, win->ray->tex_x, \
							win->ray->tex_y);
		if (win->ray->side == 1)
			map->color->color = (map->color->color >> 1) & 8355711;
		win->buffer[y][x] = map->color->color;
		y++;
	}
}

void	ft_mlx_pixel_put(t_img *texture, int x, int y, int color)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_buffer(t_data *map, \
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
