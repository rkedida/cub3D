/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/24 23:10:41 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_player_pos(t_data *map, int i, int j)
{
	map->win->pos_y = (double)i + 0.5;
	map->win->pos_x = (double)j + 0.5;
	if (map->maps[i][j] == 'N')
		set_player_direction_north(map);
	else if (map->maps[i][j] == 'S')
		set_player_direction_south(map);
	else if (map->maps[i][j] == 'W')
		set_player_direction_west(map);
	else if (map->maps[i][j] == 'E')
		set_player_direction_east(map);
}

void	set_player_direction_north(t_data *map)
{
	map->win->dir_x = 0;
	map->win->dir_y = -1.0000000001;
	map->win->plane_x = 1;
	map->win->plane_y = 0;
}

void	set_player_direction_south(t_data *map)
{
	map->win->dir_x = 0;
	map->win->dir_y = 1;
	map->win->plane_x = -1;
	map->win->plane_y = 0;
}

void	set_player_direction_west(t_data *map)
{
	map->win->dir_x = -1;
	map->win->dir_y = 0;
	map->win->plane_x = 0;
	map->win->plane_y = 1;
}

void	set_player_direction_east(t_data *map)
{
	map->win->dir_x = 1;
	map->win->dir_y = 0;
	map->win->plane_x = 0;
	map->win->plane_y = -1;
}