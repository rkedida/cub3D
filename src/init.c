/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/21 01:35:35 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_data	*init_map_struct(void)
{
	t_data	*map;

	map = malloc(sizeof(t_data));
	if (!map)
		error_exit("map struct init failed.");
	map->mlx = NULL;
	map->mlx_win = NULL;
	// input parsing
	map->map_path = NULL;
	map->check = NULL;
	map->result = 0;
	// open and read
	map->fd = 0;
	map->read_bytes = 0;
	map->map = NULL;
	map->maps = NULL;
	map->color = NULL;
	map->win = NULL;
	map->img = NULL;
	map->texture = NULL;
	return (map);
}

t_window	*init_window_struct(void)
{
	t_window	*win;

	win = malloc(sizeof(t_window));
	if (!win)
		error_exit("window struct init failed.");
	return (win);
}

t_img	*init_img_struct(void)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		error_exit("img struct init failed.");
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_length = 0;
	img->endian = 0;
	img->img_width = 0;
	img->img_height = 0;
	return (img);
}

t_texture	*init_texture_struct(void)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		error_exit("texture struct init failed.");
	texture->north_tex = NULL;
	texture->south_tex = NULL;
	texture->west_tex = NULL;
	texture->east_tex = NULL;
	texture->north_path = NULL;
	texture->south_path = NULL;
	texture->west_path = NULL;
	texture->east_path = NULL;
	texture->floor = NULL;
	texture->ceiling = NULL;
	texture->found_no = 0;
	texture->found_so = 0;
	texture->found_we = 0;
	texture->found_ea = 0;
	texture->found_f = 0;
	texture->found_c = 0;
	return (texture);
}

t_color	*init_color_struct(void)
{
	t_color	*color;

	color = malloc(sizeof(t_color));
	if (!color)
		error_exit("color struct init failed.");
	color->floor_r = 0;
	color->floor_g = 0;
	color->floor_b = 0;
	color->ceiling_r = 0;
	color->ceiling_g = 0;
	color->ceiling_b = 0;
	color->color = 0;
	return (color);
}
