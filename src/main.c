/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/10 18:49:16 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_data	*init_map_struct(void)
{
	t_data *map;

	
	map = malloc(sizeof(t_data));
	map->mlx = NULL;
	map->mlx_win = NULL;

	// input parsing
	map->map_path = NULL;
	map->check = NULL;
	map->result = 0;

	// open and read
	map->fd = 0;
	map->read_bytes = 0;

	// mapfile parsing
	// map->line = NULL;
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
	t_window *win;

	win = malloc(sizeof(t_window));
	win->map_x = 0;
	win->map_y = 0;
	win->pos_x = 16.0;
	win->pos_y = 9;
	win->dir_x = -1.0;
	win->dir_y = 0.0;
	win->plane_x = 0.0;
	win->plane_y = 1.0;
	win->camera_x = 0.0;
	win->raydir_x = 0.0;
	win->raydir_y = 0.0;
	win->sidedist_x = 0.0;
	win->sidedist_y = 0.0;
	win->deltadist_x = 0.0;
	win->deltadist_y = 0.0;
	win->perpwalldist = 0.0;
	win->step_x = 0;
	win->step_y = 0;
	win->hit = 0;
	win->side = 0;
	win->lineheight = 0;
	win->drawstart = 0;
	win->drawend = 0;
	win->wall_x = 0.0;
	win->tex_x = 0;
	win->tex_y = 0;
	win->step = 0.0;
	win->tex_pos = 0.0;
	win->tex_num = 0;
	win->time = 0;
	win->old_time = 0;
	win->frame_time = 0.0;
	// win->img_data = NULL;
	return (win);
}

t_texture	*init_texture_struct(void)
{
	t_texture *texture;

	texture = malloc(sizeof(t_texture));
	texture->north_path = NULL;
	texture->south_path = NULL;
	texture->west_path = NULL;
	texture->east_path = NULL;
	texture->found_no = 0;
	texture->found_so = 0;
	texture->found_we = 0;
	texture->found_ea = 0;
	return (texture);
}

t_color	*init_color_struct(void)
{
	t_color *color;

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

t_img	*init_img_struct(void)
{
	t_img *img;

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
	map = init_map_struct();
	map->win = init_window_struct();
	map->texture = init_texture_struct();
	map->color = init_color_struct();
	map->img = init_img_struct();
	parsing(ac, av, map);

	map->mlx = mlx_init();
	if (!map->mlx)
		error_exit("mlx_init() failed\n");
	map->mlx_win = mlx_new_window(map->mlx, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT, "cub3D");
	if (!map->mlx_win)
		error_exit("mlx_new_window() failed\n");

	// map->img->mlx_win = mlx_new_image(map->img->mlx, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT);
	// mlx_put_image_to_window(map->img->mlx, map->img->mlx_win, map->img->img, 0, 0);
	// map->img->img = mlx_new_image(map->mlx, MAX_WINDOW_WIDTH, MAX_WINDOW_HEIGHT);
	// map->img->addr = mlx_get_data_addr(map->img->img, &map->img->bpp, &map->img->line_length, &map->img->endian);
	// printf("hi\n");
	load_textures(map);
	// mlx_loop_hook(map->mlx, start_drawing, map);
	start_drawing(map);
	// mlx_put_image_to_window(map->mlx, map->win, map->img->img, 0, 0);
	// mlx_destroy_image(map->mlx, map->img->img);
	mlx_key_hook(map->mlx_win, &handle_keypress, map);
	mlx_hook(map->mlx_win, 17, 0L, cleanup_and_exit, map);
	mlx_loop(map->mlx);

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
	
	free(map->texture);
	free(map->img);
	free(map->win);
	free(map->color);
	ft_free((void **)map->map);
	free(map);
	// if ((map->max_width - 1) * map->img->img_width > MAX_WINDOW_WIDTH \
	// 	|| map->max_height * map->img->img_height > MAX_WINDOW_HEIGHT)
	// 	error_exit("Window to big max resolution 1920x1080.");
	// mlx_key_hook(map->img->mlx_win, &handle_keypress, map);
	return (0);
}
