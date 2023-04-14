/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/13 20:47:17 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	RGB(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// void set_floor()

int	start_drawing(t_data *map)
{
	mlx_clear_window(map->mlx, map->mlx_win);
	raycaster(map, map->win);
	leaks();
	draw_buffer(map, map->win->buffer);
	for (int i = 0; i < MAX_WINDOW_HEIGHT; i++)
	{
		for (int j = 0; j < MAX_WINDOW_WIDTH; j++)
		{
			map->win->buffer[i][j] = '\0';
		}
	}
	return (0);
}

int	raycaster(t_data *map, t_window *win)
{
	int	x;

	x = 0;
	while (x < MAX_WINDOW_WIDTH)
	{
		// calculate ray position and direction
		win->camera_x = 2 * x / (double)MAX_WINDOW_WIDTH - 1;
		win->raydir_x = win->dir_x + win->plane_x * win->camera_x;
		win->raydir_y = win->dir_y + win->plane_y * win->camera_x;

		// which box of the map we're in
		win->map_x = (int)win->pos_x;
		win->map_y = (int)win->pos_y;


		// length of ray from one position to next x or y-side
		win->deltadist_x = DBL_MAX;
		if (win->deltadist_x)
			win->deltadist_x = fabs(1.0 / win->raydir_x);
		win->deltadist_y = DBL_MAX;
		if (win->deltadist_y)
			win->deltadist_y = fabs(1.0 / win->raydir_y);

		win->hit = 0;
		// Calculate step and initial sideDist
		if (win->raydir_x < 0)
		{
			// what direction to step in x or y-direction (either +1 or -1)
			win->step_x = -1;
			// length of ray from current position to next x or y-side
			win->sidedist_x = (win->pos_x - win->map_x) * win->deltadist_x;
		}
		else
		{
			win->step_x = 1;
			win->sidedist_x = (win->map_x + 1.0 - win->pos_x) * win->deltadist_x;
		}
		if (win->raydir_y < 0)
		{
			win->step_y = -1;
			win->sidedist_y = (win->pos_y - win->map_y) * win->deltadist_y;
		}
		else
		{
			win->step_y = 1;
			win->sidedist_y = (win->map_y + 1.0 - win->pos_y) * win->deltadist_y;
		}

		// perform DDA
		while (win->hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (win->sidedist_x < win->sidedist_y)
			{
				win->sidedist_x += win->deltadist_x;
				win->map_x += win->step_x;
				win->side = 0;
			}
			else
			{
				win->sidedist_y += win->deltadist_y;
				win->map_y += win->step_y;
				win->side = 1;
			}
			// Check if ray has hit wall 
			if (map->maps[win->map_y][win->map_x] == '1')
				win->hit = 1;
		}

		// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect)
		if (win->side == 0)
			win->perpwalldist = (win->sidedist_x - win->deltadist_x);
		else
			win->perpwalldist = (win->sidedist_y - win->deltadist_y);

		// Calculate height of line to draw on screen
		win->lineheight = (int)(MAX_WINDOW_HEIGHT * 0.66 / win->perpwalldist);

		// Calculate lowest and highest pixel to fill in current stripe
		win->drawstart = -win->lineheight / 2 + MAX_WINDOW_HEIGHT / 2 + 100;
		if (win->drawstart < 0)
			win->drawstart = 0;
		win->drawend = win->lineheight / 2 + MAX_WINDOW_HEIGHT / 2 + 100;
		if (win->drawend >= MAX_WINDOW_HEIGHT)
			win->drawend = MAX_WINDOW_HEIGHT - 1;

		if (win->side == 0 && win->raydir_x > 0)
		{
			map->img = map->texture->north_tex;
			map->color->color = get_tex_pixel(map->texture->north_tex, win->tex_x, win->tex_y);
		}
		if (win->side == 0 && win->raydir_x < 0)
		{
			map->img = map->texture->south_tex;
			map->color->color = get_tex_pixel(map->texture->south_tex, win->tex_x, win->tex_y);
		}
		if (win->side == 1 && win->raydir_y < 0)
		{
			map->img = map->texture->west_tex;
			map->color->color = get_tex_pixel(map->texture->west_tex, win->tex_x, win->tex_y);
		}
		if (win->side == 1 && win->raydir_y > 0)
		{
			map->img = map->texture->east_tex ;
			map->color->color = get_tex_pixel(map->texture->east_tex, win->tex_x, win->tex_y);
		}

	// Set floor and ceiling colors in buffer
	for (int y = 0; y < MAX_WINDOW_HEIGHT; y++)
	{
		if (y < win->drawstart)
			win->buffer[y][x] = (unsigned int)RGB(map->color->ceiling_r, map->color->ceiling_g, map->color->ceiling_b, 125);
		else
			win->buffer[y][x] = (unsigned int)RGB(map->color->floor_r, map->color->floor_g, map->color->floor_b, 125);
	}

		// calculate value of wall_x
		if (win->side == 0)
			win->wall_x = win->pos_y + win->perpwalldist * win->raydir_y;
		else
			win->wall_x = win->pos_x + win->perpwalldist * win->raydir_x;
		win->wall_x -= floor((win->wall_x));

		// x coordinate on the texture
		win->tex_x = (int)(win->wall_x * (double)(map->img->img_width));
		if (win->side == 0 && win->raydir_x > 0)
			win->tex_x = map->img->img_width - win->tex_x - 1;
		if (win->side == 1 && win->raydir_y < 0)
			win->tex_x = map->img->img_width - win->tex_x - 1;

		// how much to increase the texture coordinate per screen pixel
		win->step = 1.0 * (double)map->img->img_height / win->lineheight;

		// starting texture coordinate
		win->tex_pos = (win->drawstart - 100 - MAX_WINDOW_HEIGHT / 2 + win->lineheight / 2) * win->step;

		for (int y = win->drawstart; y < win->drawend; y++)
		{
			// cast the texture coordinate to integer, and mask with (tex_height - 1) in case of overflow
			win->tex_y = (int)win->tex_pos & (map->img->img_height - 1);
			win->tex_pos += win->step;
			map->color->color = get_tex_pixel(map->img, win->tex_x, win->tex_y);
			if (win->side == 1)
				map->color->color = (map->color->color >> 1) & 8355711;
			win->buffer[y][x]= map->color->color;
		}
		x++;
	}
	// timinig for input and FPS counter
	win->old_time = win->time;
	win->time = clock();
	win->frame_time = (win->time - win->old_time) / 1000.0;
	printf("%f\n", 1.0 / win->frame_time); // FPS counter

	// speed modifiers
	win->move_speed = win->frame_time * 5;
	win->rot_speed = win->frame_time * 3;

	return (0);
}

void	draw_buffer(t_data *map, \
					uint32_t buffer[MAX_WINDOW_HEIGHT][MAX_WINDOW_WIDTH])
{
	int	x;
	int	y;

	y = 0;
	while (y < MAX_WINDOW_HEIGHT)
	{
		x = 0;
		while (x < MAX_WINDOW_WIDTH)
		{
			mlx_pixel_put(map->mlx, map->mlx_win, x, y, buffer[y][x]);
			x++;
		}
		y++;
	}
}

int	get_tex_pixel(t_img *texture, int x, int y)
{
	int				color;
	char			*dst;

	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
