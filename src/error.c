/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:18:51 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 21:35:36 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error_exit(char *message)
{
	if (message)
	{
		write(2, "Error: ", 7);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	else
	{
		write(2, "Error: UNKNOWN", 14);
		exit(EXIT_FAILURE);
	}
}

void	*ft_malloc(void *str, size_t size)
{
	str = malloc(size);
	if (!str)
		error_exit("malloc failed.");
	return (str);
}

void	ft_free(void **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	turn_right(t_window *win)
{
	rotate_vector(&(win->dir_x), &(win->dir_y), win->rot_speed);
	rotate_vector(&(win->plane_x), &(win->plane_y), win->rot_speed);
}

int	cleanup_and_exit(t_data *map)
{
	free_textures(map);
	free(map->texture);
	free(map->win);
	free(map->color);
	ft_free((void **)map->map);
	mlx_destroy_image(map->mlx, map->img);
	free(map);
	exit(0);
	return (0);
}
