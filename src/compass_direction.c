/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/04 01:02:36 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_no(int i, t_data *map)
{
	if (ft_strncmp(map->map[i], "NO", 2) == 0)
	{
		map->found_no++;
		if (!map->north_path)
			map->north_path = ft_split(map->map[i], ' ');
		if (map->north_path[0] && map->north_path[1] \
			&& map->north_path[2] == NULL)
		{
			map->result = access(map->north_path[1], F_OK | R_OK);
			if (map->result != 0)
				error_exit("NO path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("NO path wrong");
	}
}

void	check_so(int i, t_data *map)
{
	if (ft_strncmp(map->map[i], "SO", 2) == 0)
	{
		map->found_so++;
		if (!map->south_path)
			map->south_path = ft_split(map->map[i], ' ');
		if (map->south_path[0] && map->south_path[1] \
			&& map->south_path[2] == NULL)
		{
			map->result = access(map->south_path[1], F_OK | R_OK);
			if (map->result != 0)
				error_exit("SO path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("SO path wrong");
	}
}

void	check_we(int i, t_data *map)
{
	if (ft_strncmp(map->map[i], "WE", 2) == 0)
	{
		map->found_we++;
		if (!map->west_path)
			map->west_path = ft_split(map->map[i], ' ');
		if (map->west_path[0] && map->west_path[1] && map->west_path[2] == NULL)
		{
			map->result = access(map->west_path[1], F_OK | R_OK);
			if (map->result != 0)
				error_exit("WE path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("WE path wrong");
	}
}

void	check_ea(int i, t_data *map)
{
	if (ft_strncmp(map->map[i], "EA", 2) == 0)
	{
		map->found_ea++;
		if (!map->east_path)
			map->east_path = ft_split(map->map[i], ' ');
		if (map->east_path[0] && map->east_path[1] && map->east_path[2] == NULL)
		{
			map->result = access(map->east_path[1], F_OK | R_OK);
			if (map->result != 0)
				error_exit("EA path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("EA path wrong");
	}
}

void	check_compass_direction_in_file(int i, t_data *map)
{
	check_no(i, map);
	check_so(i, map);
	check_we(i, map);
	check_ea(i, map);
}
