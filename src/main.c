/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/21 01:36:07 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_windows_members1(t_window *win)
{
	win->map_x = 0;
	win->map_y = 0;
	win->pos_x = 0.0;
	win->pos_y = 0.0;
	win->dir_x = 0.0;
	win->dir_y = 0.0;
	win->plane_x = 0.0;
	win->plane_y = 0.0;
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
}

void	set_windows_members2(t_window *win)
{
	win->tex_x = 0;
	win->tex_y = 0;
	win->step = 0.0;
	win->tex_pos = 0.0;
	win->time = 0;
	win->old_time = 0;
	win->frame_time = 0.0;
	win->move_speed = 0.0;
	win->rot_speed = 0.0;
}

void	check_n_free(t_data *map)
{
	printf("here initialize\n");
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

void	initialize(int ac, char **av, t_data *map)
{
	map = init_map_struct();
	map->win = init_window_struct();
	set_windows_members1(map->win);
	set_windows_members2(map->win);
	map->texture = init_texture_struct();
	map->color = init_color_struct();
	map->img = init_img_struct();
	parsing(ac, av, map);
	map->mlx = mlx_init();
	error_prints(map->mlx, MLX_FAILED_INIT);
	map->mlx_win = mlx_new_window(map->mlx, MAX_WINDOW_WIDTH,
			MAX_WINDOW_HEIGHT, "cub3D");
	error_prints(map->mlx_win, MLX_FAILED_NEW_WINDW);
	map->img->img = mlx_new_image(map->mlx, MAX_WINDOW_WIDTH,
			MAX_WINDOW_HEIGHT);
	map->img->addr = mlx_get_data_addr(map->img->img, &map->img->bpp,
			&map->img->line_length, &map->img->endian);
	load_textures(map);
	mlx_loop_hook(map->mlx, &start_drawing, map);
	mlx_key_hook(map->mlx_win, &handle_keypress, map);
	mlx_hook(map->mlx_win, 17, 0L, cleanup_and_exit, map);
	mlx_loop(map->mlx);
	free_map(map);
	free(map->img);
	free(map);
}

int	main(int ac, char **av)
{
	t_data	*map;

	map = NULL;
	atexit(leaks);
	initialize(ac, av, map);
	printf("here initialize\n");
	check_n_free(map);
	return (0);
}
