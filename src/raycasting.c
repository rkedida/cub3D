/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/06 18:26:54 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

 int RGB(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// int get_pixel_color(t_data *map, int x, int y)
// {
// 	int width = map->img->img_width;
// 	int height = map->img->img_height;
// 	int *pixels = (int*)map->img->img;

// 	// Bounds check
// 	if (x < 0 || x >= width || y < 0 || y >= height) {
// 		return 0; // Return black for out-of-bounds pixels
// 	}

// 	// Retrieve pixel color
// 	int offset = y * width + x;
// 	int pixel = pixels[offset];
// 	int r = (pixel >> 16) & 0xFF;
// 	int g = (pixel >> 8) & 0xFF;
// 	int b = pixel & 0xFF;
// 	return RGB(r, g, b);
// }

void	set_floor(t_data *map)
{
	int	i;
	int	j;

	i = 0;
	map->color->color = RGB(map->color->floor_r, map->color->floor_g, map->color->floor_b, 255);
	while (i < MAX_WINDOW_HEIGHT)
	{
		j = 0;
		while (j < (MAX_WINDOW_HEIGHT / 2))
		{
			ft_mlx_pixel_put(map, i, j + (MAX_WINDOW_HEIGHT / 2), map->color->color);
			j++;
		}
		i++;
	}
}

int	ft_mlx_pixel_put(t_data *img, int x, int y, int num_color)
{
	char	*dst;

	dst = img->img->addr + (y * img->img->line_length + x * (img->img->bpp / 8));
	*(unsigned int *)dst = num_color;
	return (0);
}

// void	ft_mlx_pixel_put(t_data *mlx, int x, int y, int color)
// {
//     char *dst;

//     dst = mlx->img->addr + (y * mlx->img->line_length + x * (mlx->img->bpp / 8));
//     *(unsigned int*)dst = color;
// }

int	start_drawing(t_data *map)
{
	// load_textures(map, map->img);
	map->img->img = mlx_new_image(map->mlx, 500, 500);
	map->img->addr = mlx_get_data_addr(map->img->img, &map->img->bpp, &map->img->line_length, &map->img->endian);
	raycaster(map, map->win);
	mlx_destroy_image(map->mlx, map->img->img);
	// set_floor(map);
	// draw_buffer(map, map->win->buffer);
	// for (int y = 0; y < MAX_WINDOW_HEIGHT; y++)
	// {
	// 	for (int x = 0; x < MAX_WINDOW_WIDTH; x++)
	// 	{
	// 		map->win->buffer[y][x] = 0;
	// 	}
	// }
	printf("%d - linelength\n", map->img->line_length);
	return (0);
}

int	raycaster(t_data *map, t_window *win)
{
	int	x;
	// win->pos_x = 16;
	// win->pos_y = 9;
	// map->win->dir_x = -1;
	// map->win->dir_y = 0;
	// map->win->plane_x = 0;
	// map->win->plane_y = 0.66;
	
	x = 0;
	while (x < MAX_WINDOW_WIDTH)
	{
		// calculate ray position and direction
		win->camera_x = 2 * x / (double)MAX_WINDOW_WIDTH - 1;
		win->raydir_x = win->dir_x + win->plane_x * win->camera_x;
		win->raydir_y = win->dir_y + win->plane_y * win->camera_x;
		// printf("raydir_x = %f === raydir_y = %f === camera_x = %f\n", win->raydir_x, win->raydir_y, win->camera_x);

		// which box of the map we're in
		win->map_x = (int)win->pos_x;
		win->map_y = (int)win->pos_y;
		// printf("map_x = %d === map_y = %d\n", win->map_x, win->map_y);


		// length of ray from one position to next x or y-side to next x or y-side
		win->deltadist_x = DBL_MAX;
		if (win->deltadist_x)
			win->deltadist_x = fabs(1.0 / win->raydir_x);
		win->deltadist_y = DBL_MAX;
		if (win->deltadist_y)
			win->deltadist_y = fabs(1.0 / win->raydir_y);
		// printf("deltadist_x = %f === deltadist_y = %f\n", win->deltadist_x, win->deltadist_y);

		win->hit = 0;
		win->side = 0;
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
		// printf("perpwalldist = %f === side = %d\n", win->perpwalldist, win->side);


		// Calculate height of line to draw on screen
		// printf("lineheight before = %d\n", win->lineheight);
		win->lineheight = (int)(MAX_WINDOW_HEIGHT / win->perpwalldist);
		// printf("lineheight after = %d\n", win->lineheight);

		// set_floor(map);

		// Calculate lowest and highest pixel to fill in current stripe
		// printf("drawstart before = %d\n", win->drawstart);
		win->drawstart = -win->lineheight / 2 + MAX_WINDOW_HEIGHT / 2;
		// printf("drawstart mid = %d\n", win->drawstart);
		if (win->drawstart < 0)
			win->drawstart = 0;
		// printf("drawstart after = %d\n", win->drawstart);
		// printf("\n");
		// printf("drawend before = %d\n", win->drawend);
		win->drawend = win->lineheight / 2 + MAX_WINDOW_HEIGHT / 2;
		// printf("drawend mid = %d\n", win->drawend);
		if (win->drawend >= MAX_WINDOW_HEIGHT)
			win->drawend = MAX_WINDOW_HEIGHT - 1;
		// printf("drawend after = %d\n", win->drawend);

		// texturing calculations
		// win->tex_num = map->maps[win->map_y][win->map_x] - 1; // 1 subtracted from it so that texture 0 can be used!

		// // calculate value of wallX
		// if (win->side == 0)
		// 	win->wall_x = win->pos_y + win->raydir_y * win->perpwalldist;
		// else
		// 	win->wall_x = win->pos_x + win->raydir_x * win->perpwalldist;
		// win->wall_x -= floor((win->wall_x));


		// // x coordinate on the texture
		// win->tex_x = (int)(win->wall_x * 64);
		// if (win->side == 0 && win->raydir_x > 0)
		// 	win->tex_x = map->img->img_width - win->tex_x - 1;
		// if (win->side == 1 && win->raydir_x < 0)
		// 	win->tex_x = map->img->img_width - win->tex_x - 1;


		
		// // How much to increase the texture coordinate per screen pixel
		// win->step = 1.0 * map->img->img_height / win->lineheight;

		// Starting texture coordinate
		// win->tex_pos = (win->drawstart - 100 - MAX_WINDOW_HEIGHT / 2 + win->lineheight / 2) * win->step;
			
		// map->img->lineheight = map->img->texture[1][0];
		// int i = 0;
		// while (i < win->drawstart)
		// {
		// 	win->buffer[i][x] = RGB(map->color->ceiling_r, map->color->ceiling_g, map->color->ceiling_b);
		// 	i++;
		// }
		// i = win->drawstart;
		// while (i < win->drawend)
		// {
		// 	// Cast the texture coordinate to an integer, and mask with (texHeight - 1) in case of overflow
		// 	win->tex_y = (int)win->tex_pos & (64 - 1);
		// 	win->tex_pos += win->step;
		// 	// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// 	// map->img->lineheight = get_pixel_color(Map, map->img->tex_x, map->img->tex_y);
		// 	// win->lineheight = RGB(220, 120, 0);
		// 	if (win->side == 1)
		// 	{
		// 		win->lineheight = (win->lineheight >> 1) & 8355611;
		// 		win->buffer[x][i] = win->lineheight;
		// 	}
		// 	i++;
		// }
		// i =0;
		// while (i < MAX_WINDOW_HEIGHT / 2)
		// 	win->buffer[i++][x] = RGB(map->color->floor_r, map->color->floor_g, map->color->floor_b);
		// if (map->maps[win->map_y][win->map_x] == '1')
		// map->img->img = mlx_new_image(map->mlx, 500, 500);
		if (win->side == 0 && win->raydir_x > 0)
			map->color->color = RGB(255, 0, 0, 255);
		if (win->side == 0 && win->raydir_x < 0)
			map->color->color = RGB(0, 0, 255, 255);
		if (win->side == 1 && win->raydir_y < 0)
			map->color->color = RGB(0, 128, 0, 255);
		if (win->side == 1 && win->raydir_y > 0)
			map->color->color = RGB(255, 255, 0, 255);
		// map->img->addr = mlx_get_data_addr(map->img->img, &map->img->bpp, &map->img->line_length, &map->img->endian);
		// int	i = win->drawstart;
		// while (i < win->drawend)
		// {
			
		// 	ft_mlx_pixel_put(map, x, i, map->color->color);
		// 	i++;
		// }
		// mlx_pixel_put(map->mlx, map->mlx_win, x, win->drawstart, map->color->color);
		if (win->side == 1)
			map->color->color = map->color->color / 2;
		mlx_verline(map, x, win->drawstart, win->drawend, map->color->color);
		// printf("%d\n", map->color->color);
		// printf("%d\n", map->color->color);
		// else if (map->maps[map->img->map_y][map->img->map_x] == '0')
		// else
			
		// mlx_pixel_put(map->img->mlx, map->img->mlx_win, map->img->drawstart, map->img->drawend, map->color->color);
		// printf("%d - y1 === %d - y2\n", map->img->drawstart, map->img->drawend);

		x++;
	}
		// mlx_put_image_to_window(map->mlx, map->mlx_win, map->img->img, 0, 0);
		// mlx_put_image_to_window(map->mlx, map->mlx_win, map->img->img, 0, 0);

		// mlx_pixel_put(map->mlx, map->mlx_win, map->win->drawstart, map->win->drawend, map->color->color);
	// timinig for input and FPS counter
	win->old_time = win->time;
	win->time = clock();
	win->frame_time = (win->time - win->old_time) / 1000.0;
	printf("%f\n", 1.0 / win->frame_time); // FPS counter

	// Draw the image to the window
	
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img, 0, 0);
	// mlx_destroy_image(map->mlx, map->img->img);

	// speed modifiers
	win->move_speed = win->frame_time * 5.0;
	win->rot_speed = win->frame_time * 3.0;
	

	// draw_buffer(map, map->mlx, map->mlx_win, map->img->img_width, map->img->img_height, &map->color->color);

	// draw_buffer(map->img->mlx, map->img->mlx_win, map->img->img_width, map->img->img_height, map->img->buffer[0]);
	// printf("%d - x === %d - drawstart === %d - drawend\n", x, map->img->drawstart, map->img->drawend);
	// draw_buffer(map, win->buffer);
	// for (int y = 0; y < MAX_WINDOW_HEIGHT; y++)
	// {
	// 	for (int x = 0; x < MAX_WINDOW_WIDTH; x++)
	// 	{
	// 		win->buffer[y][x] = 0;
	// 	}
	// }
	return (0);
}

// void draw_buffer(t_data *map, u_int32_t buffer[MAX_WINDOW_HEIGHT][MAX_WINDOW_WIDTH])
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	(void)buffer;
// 	while (i < MAX_WINDOW_HEIGHT)
// 	{
// 		j = 0;
// 		while (j < MAX_WINDOW_WIDTH)
// 		{
// 			mlx_pixel_put(map->mlx, map->mlx_win, i, j, map->color->color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void draw_buffer(t_data *map, void *mlx, void *win, int w, int h, unsigned int *buffer)
// {
// 	map->img->img = mlx_new_image(mlx, w, h);
// 	map->img->img = mlx_get_image_data(map->img->img, &w, &h);
// 	unsigned int *bufp = mlx_get_data_addr(map->img->img, &map->img->bpp, &map->img->line_length, &map->img->endian);


// 	for(int y = 0; y < h; y++)
// 	{
// 		for(int x = 0; x < w; x++)
// 		{
// 			*bufp = buffer[y * w + x];
// 			bufp++;
// 		}
// 		bufp += map->img->line_length / 4;
// 		bufp -= w;
// 	}

// 	map->img->img = mlx_new_image(mlx, w, h);
// 	map->img->img = mlx_get_image_data(map->img->img, &w, &h);
// 	mlx_put_image_to_window(mlx, win, map->img->img, 0, 0);
// }

// void draw_buffer(t_data *map, void *mlx, void *win, int w, int h, unsigned int *buffer)
// {
//     int *img_data = (int *)mlx_get_data_addr(map->img->img, &map->img->bpp, &map->img->line_length, &map->img->endian);

//     for (int y = 0; y < h; y++)
//     {
//         for (int x = 0; x < w; x++)
//         {
//             if (y < map->img->img_height && x < map->img->img_width) {
//                  int *pixel = img_data + (y * map->img->line_length / 4) + x;
//                 *pixel = buffer[y * w + x];
//             }
//         }
//     }

    // mlx_put_image_to_window(mlx, win, map->img->img, 0, 0);
// }


void ft_swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

bool mlx_verline(t_data *map, int x, int y1, int y2,  int color)
{
	int y;
	(void)color;
	if (y2 < y1) {
		ft_swap(&y1, &y2);
	}
	
	if (y2 < 0 || y1 >= MAX_WINDOW_HEIGHT || x < 0 || x >= MAX_WINDOW_WIDTH) {
		return false;
	}
	
	if (y1 < 0) {
		y1 = 0;
	}
	
	if (y2 >= MAX_WINDOW_WIDTH) {
		y2 = MAX_WINDOW_HEIGHT - 1;
	}

	map->win->drawstart = y1;
	map->win->drawend = y2;

	y = map->win->drawstart;
	while (y <= map->win->drawend) {
		mlx_pixel_put(map->mlx, map->mlx_win, x, y, map->color->color);
		y++;
	}

	return true;
}

// bool mlx_verline(t_data *map, int x, int y1, int y2, int color)
// {
// 	if (y2 < y1) {
// 		ft_swap(&y1, &y2);
// 	}

// 	if (y2 < 0 || y1 >= MAX_WINDOW_HEIGHT || x < 0 || x >= MAX_WINDOW_WIDTH) {
// 		return false;
// 	}

// 	if (y1 < 0) {
// 		y1 = 0;
// 	}

// 	if (y2 >= MAX_WINDOW_HEIGHT) {
// 		y2 = MAX_WINDOW_HEIGHT - 1;
// 	}
// 	// printf("hi\n");
// 	//  color = (255 << 24) | (220 << 16) | (0 << 8) | (255);
// 	char *dst = map->img->addr + (x * map->img->bpp / 8) + (y1 * map->img->line_length);
// 	for (int y = y1; y <= y2; y++) {
// 		// mlx_pixel_put(map->mlx, map->mlx_win, x, y, color);
// 		*(int*)dst = color;
// 		dst += map->img->line_length;
// 	}

// 	return true;
// }