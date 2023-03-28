/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/27 23:11:47 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*init_map_struct(t_mapData *Map)
{
	Map = malloc(sizeof(t_mapData));
	// input parsing
	Map->map_path = NULL;
	Map->check = NULL;
	Map->result = 0;

	// open and read
	Map->fd = 0;
	Map->read_bytes = 0;

	// mapfile parsing
	Map->line = NULL;
	Map->map = NULL;
	Map->maps = NULL;
	Map->north_path = NULL;
	Map->south_path = NULL;
	Map->west_path = NULL;
	Map->east_path = NULL;
	Map->found_NO = 0;
	Map->found_SO = 0;
	Map->found_WE = 0;
	Map->found_EA = 0;

	Map->max_width = 0;
	Map->max_height = 0;
	Map->rows = 0;
	Map->cols = 0;


	
	Map->total_cols = 0;
	Map->player = 0;
	Map->num_collectibles = 0;
	Map->max_collectibles = 0;
	Map->num_exits = 0;
	Map->visited = NULL;
	Map->found_exit = false;
	Map->img = NULL;
	Map->steps = 0;
	Map->found_map = false;
	return (Map);
}

void	*init_windata(t_winData *img)
{
	img = malloc(sizeof(t_winData));
	img->mlx = NULL;
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_length = 0;
	img->endian = 0;
	img->img_width = 55;
	img->img_height = 55;
	img->relative_path = NULL;
	return (img);
}

void	*init_color(t_color *color)
{
	color = malloc(sizeof(t_color));
	color->floor_r = 0;
	color->floor_g = 0;
	color->floor_b = 0;
	color->ceiling_r = 0;
	color->ceiling_g = 0;
	color->ceiling_b = 0;
	return (color);
}

void	leaks(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_mapData	*map;

	leaks();
	atexit(leaks);
	map = NULL;
	map = init_map_struct(map);
	map->img = init_windata(map->img);
	map->color = init_color(map->color);
	parsing(ac, av, map);
	printf("hi\n");

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
	// ft_free((void **)map->maps, map);
	ft_free((void **)map->map);
	free(map->color);
	free(map->img);
	free(map);
	// if ((map->max_width - 1) * map->img->img_width > MAX_WINDOW_WIDTH \
	// 	|| map->max_height * map->img->img_height > MAX_WINDOW_HEIGHT)
	// 	error_exit("Window to big max resolution 1920x1080.");
	// map->img->mlx = mlx_init();
	// map->img->mlx_win = mlx_new_window(map->img->mlx, \
	// 	(map->max_width - 1) * map->img->img_width, \
	// 		(map->max_height) * map->img->img_height, "Balu");
	// load_textures(map, map->img);
	// mlx_key_hook(map->img->mlx_win, &handle_keypress, map);
	// mlx_hook(map->img->mlx_win, 17, 0L, cleanup_and_exit, map);
	// mlx_loop(map->img->mlx);
	return (0);
}
