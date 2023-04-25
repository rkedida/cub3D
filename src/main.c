/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 21:42:03 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	leaks(void)
{
	system("leaks cub3D");
}

void	init_window(t_data *map)
{
	map->mlx = mlx_init();
	if (!map->mlx)
		error_exit("mlx_init() failed\n");
	map->mlx_win = mlx_new_window(map->mlx, MAX_WINDOW_WIDTH, \
		MAX_WINDOW_HEIGHT, "cub3D");
	if (!map->mlx_win)
		error_exit("mlx_new_window() failed\n");
	map->img->img = mlx_new_image(map->mlx, MAX_WINDOW_WIDTH, \
		MAX_WINDOW_HEIGHT);
	map->img->addr = mlx_get_data_addr(map->img->img, &map->img->bpp, \
							&map->img->line_length, &map->img->endian);
}

t_ray	*init_ray_struct(void)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->camera_x = 0;
	ray->raydir_x = 0;
	ray->raydir_y = 0;
	ray->raydir_x = 0;
	ray->raydir_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->perpwalldist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->lineheight = 0;
	ray->drawstart = 0;
	ray->drawend = 0;
	ray->tex_x = 0;
	ray->tex_y = 0;
	ray->step = 0;
	return (ray);
}

int	main(int ac, char **av)
{
	t_data	*map;

	map = init_map_struct();
	map->win = init_window_struct();
	map->win->ray = init_ray_struct();
	if (!map->win->ray)
		error_exit("Error allocating memory for ray struct.");
	map->texture = init_texture_struct();
	map->color = init_color_struct();
	map->img = init_img_struct();
	parsing(ac, av, map);
	init_window(map);
	load_textures(map);
	mlx_loop_hook(map->mlx, &start_drawing, map);
	mlx_hook(map->mlx_win, 2, 0, &handle_keypress, map);
	mlx_hook(map->mlx_win, 3, 0, &handle_keypress_release, map);
	mlx_hook(map->mlx_win, 17, 0L, cleanup_and_exit, map);
	mlx_loop(map->mlx);
	return (0);
}
