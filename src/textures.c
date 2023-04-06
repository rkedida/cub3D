/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/05 02:16:16 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int	load_textures(t_data *data, t_img *img)
{
	int width, height;
	data->win->texture = malloc(4 * sizeof(int *));
	if (!data->win->texture)
		return (-1);
	img->img = mlx_xpm_file_to_image(data->mlx, data->north_path[1], &width, &height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	img->img_width = width;
	img->img_height = height;
	// printf("%d === 1texture\n", data->img->texture[1][0]);
	// if (!data->win->texture[0] || !data->win->texture[1] || !data->win->texture[2] || !data->win->texture[3])
	// {
	// 	free(data->win->texture);
	// 	return (-1);
	// }
	return (0);
}

int	cleanup_and_exit(t_data *map)
{
	mlx_destroy_window(map->mlx, map->mlx_win);
	if (map->north_path != NULL)
		ft_free((void **)map->north_path);
	if (map->south_path != NULL)
		ft_free((void **)map->south_path);
	if (map->west_path != NULL)
		ft_free((void **)map->west_path);
	if (map->east_path != NULL)
		ft_free((void **)map->east_path);
	if (map->floor != NULL)
		ft_free((void **)map->floor);
	if (map->ceiling != NULL)
		ft_free((void **)map->ceiling);
	free(map->win->texture);
	free(map->win);
	free(map->img);
	free(map->color);
	ft_free((void **)map->map);
	free(map);
	exit(0);
	return (0);
}
