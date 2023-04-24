/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/24 15:09:35 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	leaks(void)
{
	system("leaks cub3D");
}

void	ft_mlx_pixel_put(t_img *texture, int x, int y, int color)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_buffer(t_data *map,
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
			ft_mlx_pixel_put(map->img, x, y, buffer[y][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img->img, 0, 0);
}

int	get_tex_pixel(t_img *texture, int x, int y)
{
	int				color;
	char			*dst;

	color = 0;
	dst = NULL;
	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}
