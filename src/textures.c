/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/10 16:59:52 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_texture(t_data *map, char *path, t_img *img)
{
	int	width;
	int	height;

	printf("path: %s \n", path);

	width = 0;
	height = 0;
	img->img = mlx_xpm_file_to_image(map->mlx, path, &width, &height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	// printf("addr: %p, bpp: %d, line_length: %d, endian: %d \n", img->addr, img->bpp, img->line_length, img->endian);
	img->img_width = width;
	img->img_height = height;
	return (0);
}

int	load_textures(t_data *map)
{
	map->texture->north_tex = malloc(sizeof(t_img));
	ft_memset(map->texture->north_tex, 0, sizeof(t_img));
	map->texture->south_tex = malloc(sizeof(t_img));
	ft_memset(map->texture->south_tex, 0, sizeof(t_img));
	map->texture->west_tex = malloc(sizeof(t_img));
	ft_memset(map->texture->west_tex, 0, sizeof(t_img));
	map->texture->east_tex = malloc(sizeof(t_img));
	ft_memset(map->texture->east_tex, 0, sizeof(t_img));
	load_texture(map, map->texture->north_path[1], map->texture->north_tex);
	load_texture(map, map->texture->south_path[1], map->texture->south_tex);
	load_texture(map, map->texture->west_path[1], map->texture->west_tex);
	load_texture(map, map->texture->east_path[1], map->texture->east_tex);
	return (0);
}

int	cleanup_and_exit(t_data *map)
{
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
	if (map->texture->north_tex != NULL)
		free(map->texture->north_tex);
	if (map->texture->south_tex != NULL)
		free(map->texture->south_tex);
	if (map->texture->west_tex != NULL)
		free(map->texture->west_tex);
	if (map->texture->east_tex != NULL)
		free(map->texture->east_tex);
	
	free(map->win->texture);
	free(map->texture);
	free(map->img);
	free(map->win);
	free(map->color);
	ft_free((void **)map->map);
	free(map);
	exit(0);
	return (0);
}
