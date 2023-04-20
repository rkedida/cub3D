/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/20 19:32:14 by sheali           ###   ########.fr       */
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
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length,
			&img->endian);
	// printf("addr: %p, bpp: %d, line_length: %d, endian: %d \n", img->addr, img->bpp, img->line_length, img->endian);
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
	if (map->texture->north_path[1] != NULL)
		load_texture(map, map->texture->north_path[1], map->texture->north_tex);
	if (map->texture->south_path[1] != NULL)
		load_texture(map, map->texture->south_path[1], map->texture->south_tex);
	if (map->texture->west_path[1] != NULL)
		load_texture(map, map->texture->west_path[1], map->texture->west_tex);
	if (map->texture->east_path[1] != NULL)
		load_texture(map, map->texture->east_path[1], map->texture->east_tex);
	return (0);
}

int	cleanup_and_exit(t_data *map)
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
	free_map(map);
	mlx_destroy_image(map->mlx, map->img);
	exit(0);
	free(map);
	return (0);
}
