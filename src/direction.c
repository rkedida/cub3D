/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:42:04 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 18:08:41 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_no_so(t_data *map, int i, int j)
{
	if (map->maps[i][j] == 'N')
	{
		map->win->pos_y = (double)i;
		map->win->pos_x = (double)j + 0.5;
		map->win->dir_x = 0;
		map->win->dir_y = -1.000001;
		map->win->plane_x = -0.66;
		map->win->plane_y = 0;
	}
	if (map->maps[i][j] == 'S')
	{
		map->win->pos_y = (double)i;
		map->win->pos_x = (double)j + 0.5;
		map->win->dir_x = 0;
		map->win->dir_y = 1.000001;
		map->win->plane_x = 0.66;
		map->win->plane_y = 0;
	}
}

void	set_we_ea(t_data *map, int i, int j)
{
	if (map->maps[i][j] == 'W')
	{
		map->win->pos_y = (double)i + 0.5;
		map->win->pos_x = (double)j;
		map->win->dir_x = -1.000001;
		map->win->dir_y = 0;
		map->win->plane_x = 0;
		map->win->plane_y = -0.66;
	}
	if (map->maps[i][j] == 'E')
	{
		map->win->pos_y = (double)i + 0.5;
		map->win->pos_x = (double)j;
		map->win->dir_x = 1.000001;
		map->win->dir_y = 0;
		map->win->plane_x = 0;
		map->win->plane_y = 0.66;
	}
}

void	set_player_pos(t_data *map, int i, int j)
{
	set_no_so(map, i, j);
	set_we_ea(map, i, j);
}

void	check_no_so(t_data *map, t_texture *texture, int i, int j)
{
	if (map->maps[i][j] == 'N')
	{
		if (check_flags(texture))
			texture->found_no++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
	}
	else if (map->maps[i][j] == 'S')
	{
		if (check_flags(texture))
			texture->found_so++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
	}
}

void	check_we_ea(t_data *map, t_texture *texture, int i, int j)
{
	if (map->maps[i][j] == 'W')
	{
		if (check_flags(texture))
			texture->found_we++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
	}
	else if (map->maps[i][j] == 'E')
	{
		if (check_flags(texture))
			texture->found_ea++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
	}
}
