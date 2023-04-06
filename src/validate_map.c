/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/05 23:40:34 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_flags(t_data *map)
{
	if (!map->found_no && !map->found_so && !map->found_we && !map->found_ea)
		return (true);
	// else
	// 	error_exit("Only one Player Direction allowed.");
	return (false);
}

void	set_player_pos(t_data *map, int i, int j)
{
		map->win->pos_y = i;
		map->win->pos_x = j;

		if (map->maps[i][j] == 'N')
		{
			map->win->dir_x = -1;
			map->win->dir_y = 0;
			map->win->plane_x = 0;
			map->win->plane_y = 1;
		}
		if (map->maps[i][j] == 'S')
		{
			map->win->dir_x = 1;
			map->win->dir_y = 0;
			map->win->plane_x = 0;
			map->win->plane_y = -1;
		}
		if (map->maps[i][j] == 'W')
		{
			map->win->dir_x = -1;
			map->win->dir_y = 0;
			map->win->plane_x = 0;
			map->win->plane_y = 1;
		}
		if (map->maps[i][j] == 'E')
		{
			map->win->dir_x = 1;
			map->win->dir_y = 0;
			map->win->plane_x = 0;
			map->win->plane_y = -1;
		}
}

void	track_map_data(t_data *map, int i, int j)
{
	if (map->maps[i][j] == 'N')
	{
		if (check_flags(map))
			map->found_no++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
		map->maps[i][j] = '0';
	}
	else if (map->maps[i][j] == 'S')
	{
		if (check_flags(map))
			map->found_so++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
		map->maps[i][j] = '0';
	}
	else if (map->maps[i][j] == 'W')
	{
		if (check_flags(map))
			map->found_we++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
		map->maps[i][j] = '0';
	}
	else if (map->maps[i][j] == 'E')
	{
		if (check_flags(map))
			map->found_ea++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(map, i, j);
		map->maps[i][j] = '0';
	}
}

void	check_map_syntax(t_data *map)
{
	int	i;
	int	j;

	i = 0;
	map->found_no = 0;
	map->found_so = 0;
	map->found_we = 0;
	map->found_ea = 0;
	while (map->maps[i] != NULL)
	{
		j = 0;
		while (map->maps[i][j] != '\0')
		{
			if (ft_strchr("01NSWE ", map->maps[i][j]))
				track_map_data(map, i, j);
			else
				error_exit("Invalid character in Map.");
			j++;
		}
		i++;
	}
	if (check_flags(map))
		error_exit("Only one Player Direction allowed.");
}

void	validate_map(t_data *map)
{
	check_map_syntax(map);
	if (check_surrounded_walls(map) == false)
		error_exit("Map not closed");
	printf("%d - rows ==== %d - cols\n", map->player_pos[0], map->player_pos[1]);
}
