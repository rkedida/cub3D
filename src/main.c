/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/05 22:16:25 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*init_map_struct(t_data *Map)
{
	Map = malloc(sizeof(t_data));
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
	Map->found_no = 0;
	Map->found_so = 0;
	Map->found_we = 0;
	Map->found_ea = 0;

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
	// Map->found_map = false;
	return (Map);
}

void	*init_window_struct(t_window *img)
{
	img = malloc(sizeof(t_window));
	// img->mlx = NULL;
	// img->img = NULL;
	// img->addr = NULL;
	// img->bpp = 0;
	// img->line_length = 0;
	// img->endian = 0;
	// img->img_width = 55;
	// img->img_height = 55;
	// img->relative_path = NULL;

	img->map_x = 0;
	img->map_y = 0;
	img->pos_x = 0.0;
	img->pos_y = 0.0;
	img->dir_x = 0.0;
	img->dir_y = 0.0;
	img->plane_x = 0.0;
	img->plane_y = 0.0;
	img->camera_x = 0.0;
	img->raydir_x = 0.0;
	img->raydir_y = 0.0;
	img->sidedist_x = 0.0;
	img->sidedist_y = 0.0;
	img->deltadist_x = 0.0;
	img->deltadist_y = 0.0;
	img->perpwalldist = 0.0;
	img->step_x = 0;
	img->step_y = 0;
	img->hit = 0;
	img->side = 0;
	img->lineheight = 0;
	img->drawstart = 0;
	img->drawend = 0;
	img->wall_x = 0.0;
	img->tex_x = 0;
	img->tex_y = 0;
	img->step = 0.0;
	img->tex_pos = 0.0;
	img->tex_num = 0;
	img->time = 0;
	img->old_time = 0;
	img->frame_time = 0.0;
	return (img);
}

void	*init_color_struct(t_color *color)
{
	color = malloc(sizeof(t_color));
	color->floor_r = 0;
	color->floor_g = 0;
	color->floor_b = 0;
	color->ceiling_r = 0;
	color->ceiling_g = 0;
	color->ceiling_b = 0;
	color->color = 0;
	return (color);
}

void	*init_img_struct(t_img *img)
{
	img = malloc(sizeof(t_img));
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_length = 0;
	img->endian = 0;
	img->img_width = 55;
	img->img_height = 55;
	return (img);
}

void	leaks(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	*map;

	leaks();
	atexit(leaks);
	map = NULL;
	map = init_map_struct(map);
	map->win = init_window_struct(map->win);
	map->color = init_color_struct(map->color);
	map->img = init_img_struct(map->img);
	parsing(ac, av, map);

	map->mlx = mlx_init();
	map->mlx_win = mlx_new_window(map->mlx, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT, "cub3D");

	// map->img->mlx_win = mlx_new_image(map->img->mlx, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT);
	// mlx_put_image_to_window(map->img->mlx, map->img->mlx_win, map->img->img, 0, 0);
	mlx_loop_hook(map->mlx, start_drawing, map);
	mlx_key_hook(map->mlx_win, &handle_keypress, map);
	mlx_hook(map->mlx_win, 17, 0L, cleanup_and_exit, map);
	mlx_loop(map->mlx);
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
	// if (map->img->texture != NULL)
	free(map->win->texture);
	free(map->win);
	free(map->color);
	free(map->img);
	ft_free((void **)map->map);
	free(map);
	// if ((map->max_width - 1) * map->img->img_width > MAX_WINDOW_WIDTH \
	// 	|| map->max_height * map->img->img_height > MAX_WINDOW_HEIGHT)
	// 	error_exit("Window to big max resolution 1920x1080.");
	// mlx_key_hook(map->img->mlx_win, &handle_keypress, map);
	return (0);
}
