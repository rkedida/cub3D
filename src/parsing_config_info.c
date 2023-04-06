/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/04 00:58:40 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_floor_rgbs(int i, t_data *map)
{
	if (ft_strncmp(map->map[i], "F", 1) == 0)
	{
		map->found_f++;
		if (!map->floor)
			map->floor = ft_split(map->map[i], ',');
		if (map->floor != NULL && map->floor[0] != NULL \
			&& map->floor[1] != NULL && map->floor[2] != NULL \
				&& map->floor[3] == NULL)
		{
			map->color->floor_r = ft_atoi(map->floor[0] + 2);
			map->color->floor_g = ft_atoi(map->floor[1]);
			map->color->floor_b = ft_atoi(map->floor[2]);
			if (map->color->floor_r < 0 || map->color->floor_g < 0 \
				|| map->color->floor_b < 0)
				error_exit("RGB failed");
		}
		else
			error_exit("Failed Floor RGB.");
	}
}

void	check_ceiling_rgbs(int i, t_data *map)
{
	if (ft_strncmp(map->map[i], "C", 1) == 0)
	{
		map->found_c++;
		if (!map->ceiling)
			map->ceiling = ft_split(map->map[i], ',');
		if (map->ceiling != NULL && map->ceiling[0] != NULL \
			&& map->ceiling[1] != NULL && map->ceiling[2] != NULL \
				&& map->ceiling[3] == NULL)
		{
			map->color->ceiling_r = ft_atoi(map->ceiling[0] + 2);
			map->color->ceiling_g = ft_atoi(map->ceiling[1]);
			map->color->ceiling_b = ft_atoi(map->ceiling[2]);
			if (map->color->ceiling_r < 0 || map->color->ceiling_g < 0 \
				|| map->color->ceiling_b < 0)
				error_exit("RGB failed");
		}
		else
			error_exit("Failed Ceiling RGB.");
	}
}

void	parsing_config_info(t_data *map)
{
	int	i;

	i = 0;
	while (map->map[i] != NULL)
	{
		check_compass_direction_in_file(i, map);
		check_floor_rgbs(i, map);
		check_ceiling_rgbs(i, map);
		i++;
	}
	if (map->north_path == NULL && map->south_path == NULL \
		&& map->west_path == NULL && map->east_path == NULL \
		&& map->floor == NULL && map->ceiling == NULL)
		map->maps = map->map;
	else if (map->found_no != 1 || map->found_so != 1 || map->found_we != 1 \
		|| map->found_ea != 1 || map->found_f != 1 || map->found_c != 1)
		error_exit("Compass Invalid Path");
	else
		map->maps = map->map + 6;
}
