/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/28 14:36:02 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_floor_rgbs(int i, t_mapData *Map)
{
	if (ft_strncmp(Map->map[i], "F", 1) == 0)
	{
		Map->found_f++;
		if (!Map->floor)
			Map->floor = ft_split(Map->map[i], ',');
		if (Map->floor != NULL && Map->floor[0] != NULL \
			&& Map->floor[1] != NULL && Map->floor[2] != NULL \
				&& Map->floor[3] == NULL)
		{
			Map->color->floor_r = ft_atoi(Map->floor[0] + 2);
			Map->color->floor_g = ft_atoi(Map->floor[1]);
			Map->color->floor_b = ft_atoi(Map->floor[2]);
			if (Map->color->floor_r < 0 || Map->color->floor_g < 0 \
				|| Map->color->floor_b < 0)
				error_exit("RGB failed");
		}
		else
			error_exit("Failed Floor RGB.");
	}
}

void	check_ceiling_rgbs(int i, t_mapData *Map)
{
	if (ft_strncmp(Map->map[i], "C", 1) == 0)
	{
		Map->found_c++;
		if (!Map->ceiling)
			Map->ceiling = ft_split(Map->map[i], ',');
		if (Map->ceiling != NULL && Map->ceiling[0] != NULL \
			&& Map->ceiling[1] != NULL && Map->ceiling[2] != NULL \
				&& Map->ceiling[3] == NULL)
		{
			Map->color->ceiling_r = ft_atoi(Map->ceiling[0] + 2);
			Map->color->ceiling_g = ft_atoi(Map->ceiling[1]);
			Map->color->ceiling_b = ft_atoi(Map->ceiling[2]);
			if (Map->color->ceiling_r < 0 || Map->color->ceiling_g < 0 \
				|| Map->color->ceiling_b < 0)
				error_exit("RGB failed");
		}
		else
			error_exit("Failed Ceiling RGB.");
	}
}

void	parsing_config_info(t_mapData *Map)
{
	int	i;

	i = 0;
	while (Map->map[i] != NULL)
	{
		check_compass_direction_in_file(i, Map);
		check_floor_rgbs(i, Map);
		check_ceiling_rgbs(i, Map);
		i++;
	}
	if (Map->north_path == NULL && Map->south_path == NULL \
		&& Map->west_path == NULL && Map->east_path == NULL \
		&& Map->floor == NULL && Map->ceiling == NULL)
		Map->maps = Map->map;
	else if (Map->found_no != 1 || Map->found_so != 1 || Map->found_we != 1 \
		|| Map->found_ea != 1 || Map->found_f != 1 || Map->found_c != 1)
		error_exit("Compass Invalid Path");
	else
		Map->maps = Map->map + 6;
}
