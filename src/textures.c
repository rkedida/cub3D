/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 21:35:16 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_texture(t_data *map, char *path, t_img *img)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	img->img = mlx_xpm_file_to_image(map->mlx, path, &width, &height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, \
															&img->endian);
	img->img_width = width;
	img->img_height = height;
	return (0);
}

int	load_textures(t_data *map)
{
	map->texture->north_tex = malloc(sizeof(t_img));
	ft_memset(map->texture->north_tex, 0, sizeof(t_img));
	if (!map->texture->north_tex)
		error_exit("Error allocating memory for north texture.");
	map->texture->south_tex = malloc(sizeof(t_img));
	ft_memset(map->texture->south_tex, 0, sizeof(t_img));
	if (!map->texture->south_tex)
		error_exit("Error allocating memory for south texture.");
	map->texture->west_tex = malloc(sizeof(t_img));
	ft_memset(map->texture->west_tex, 0, sizeof(t_img));
	if (!map->texture->west_tex)
		error_exit("Error allocating memory for west texture.");
	map->texture->east_tex = malloc(sizeof(t_img));
	ft_memset(map->texture->east_tex, 0, sizeof(t_img));
	if (!map->texture->east_tex)
		error_exit("Error allocating memory for east texture.");
	if (map->texture->north_path != NULL)
		load_texture(map, map->texture->north_path[1], map->texture->north_tex);
	if (map->texture->south_path != NULL)
		load_texture(map, map->texture->south_path[1], map->texture->south_tex);
	if (map->texture->west_path != NULL)
		load_texture(map, map->texture->west_path[1], map->texture->west_tex);
	if (map->texture->east_path != NULL)
		load_texture(map, map->texture->east_path[1], map->texture->east_tex);
	else
		load_colors(map);
	return (0);
}

void	set_color(t_data *map, t_img *texture, unsigned int color)
{
	int	i;

	if (texture == NULL)
		return ;
	if (texture->img == NULL)
	{
		texture->img_width = 64;
		texture->img_height = 64;
		texture->img = mlx_new_image(map->mlx, texture->img_width, \
									texture->img_height);
		texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, \
									&texture->line_length, &texture->endian);
	}
	i = 0;
	while (i < texture->img_width * texture->img_height)
	{
		*(unsigned int *)(texture->addr + i * (texture->bpp / 8)) = color;
		i++;
	}
}

int	load_colors(t_data *map)
{
	map->color->color = rgb(0, 0, 128, 255);
	set_color(map, map->texture->north_tex, map->color->color);
	map->color->color = rgb(255, 219, 88, 255);
	set_color(map, map->texture->south_tex, map->color->color);
	map->color->color = rgb(0, 255, 255, 100);
	set_color(map, map->texture->west_tex, map->color->color);
	map->color->color = rgb(64, 224, 208, 255);
	set_color(map, map->texture->east_tex, map->color->color);
	map->color->floor_r = 75;
	map->color->floor_g = 75;
	map->color->floor_b = 75;
	map->color->ceiling_r = 152;
	map->color->ceiling_g = 255;
	map->color->ceiling_b = 127;
	return (0);
}

void	free_textures(t_data *map)
{
	if (map->texture->north_tex != NULL)
		free(map->texture->north_tex);
	if (map->texture->south_tex != NULL)
		free(map->texture->south_tex);
	if (map->texture->west_tex != NULL)
		free(map->texture->west_tex);
	if (map->texture->east_tex != NULL)
		free(map->texture->east_tex);
	if (map->texture->north_path != NULL)
		ft_free((void **)map->texture->north_path);
	if (map->texture->south_path != NULL)
		ft_free((void **)map->texture->south_path);
	if (map->texture->west_path != NULL)
		ft_free((void **)map->texture->west_path);
	if (map->texture->east_path != NULL)
		ft_free((void **)map->texture->east_path);
	if (map->texture->floor != NULL)
		ft_free((void **)map->texture->floor);
	if (map->texture->ceiling != NULL)
		ft_free((void **)map->texture->ceiling);
}
