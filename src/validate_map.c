/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/23 15:04:19 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_flags(t_texture *texture)
{
	if (!texture->found_no && !texture->found_so && !texture->found_we && !texture->found_ea)
		return (true);
	// else
	// 	error_exit("Only one Player Direction allowed.");
	return (false);
}

void	set_player_pos(t_data *map, int i, int j)
{

		if (map->maps[i][j] == 'N')
		{
			map->win->pos_y = i;
			map->win->pos_x = j;
			map->win->dir_x = -1;
			map->win->dir_y = 0;
			map->win->plane_x = 0;
			map->win->plane_y = 1;
		}
		if (map->maps[i][j] == 'S')
		{
			map->win->pos_y = (double)i;
			map->win->pos_x = (double)j;
			map->win->dir_x = 1;
			map->win->dir_y = 0;
			map->win->plane_x = 0;
			map->win->plane_y = -1;
		}
		if (map->maps[i][j] == 'W')
		{
			map->win->pos_y = i;
			map->win->pos_x = j;
			map->win->dir_x = 0;
			map->win->dir_y = -1;
			map->win->plane_x = -1;
			map->win->plane_y = 0;
		}
		if (map->maps[i][j] == 'E')
		{
			map->win->pos_y = i;
			map->win->pos_x = j;
			map->win->dir_x = 0;
			map->win->dir_y = 1;
			map->win->plane_x = 1;
			map->win->plane_y = 0;
		}
}

void	track_map_data(t_data *map, t_texture *texture, int i, int j)
{
	if (map->maps[i][j] == 'N')
	{
		if (check_flags(texture))
			texture->found_no++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
		// map->maps[i][j] = '0';
	}
	else if (map->maps[i][j] == 'S')
	{
		if (check_flags(texture))
			texture->found_so++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
		// map->maps[i][j] = '0';
	}
	else if (map->maps[i][j] == 'W')
	{
		if (check_flags(texture))
			texture->found_we++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
		// map->maps[i][j] = '0';
	}
	else if (map->maps[i][j] == 'E')
	{
		if (check_flags(texture))
			texture->found_ea++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
		// map->maps[i][j] = '0';
	}
}

void	check_map_syntax(t_data *map, t_texture *texture)
{
	int	i;
	int	j;

	i = 0;
	texture->found_no = 0;
	texture->found_so = 0;
	texture->found_we = 0;
	texture->found_ea = 0;
	while (map->maps[i] != NULL)
	{
		j = 0;
		while (map->maps[i][j] != '\0')
		{
			if (ft_strchr("01NSWE ", map->maps[i][j]))
				track_map_data(map, texture, i, j);
			else
				error_exit("Invalid character in Map.");
			j++;
		}
		i++;
	}
	if (check_flags(texture))
		error_exit("Only one Player Direction allowed.");
}

void	validate_map(t_data *map, t_texture *texture)
{
	check_map_syntax(map, texture);
	if (check_surrounded_walls(map) == false)
		error_exit("Map not closed");
	// printf("%d - rows ==== %d - cols\n", map->player_pos[0], map->player_pos[1]);
}
