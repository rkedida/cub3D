/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/23 15:04:08 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_no(int i, t_data *map, t_texture *texture)
{
	if (ft_strncmp(map->map[i], "NO", 2) == 0)
	{
		texture->found_no++;
		if (!texture->north_path)
			texture->north_path = ft_split(map->map[i], ' ');
		if (texture->north_path[0] && texture->north_path[1] \
			&& texture->north_path[2] == NULL)
		{
			map->result = access(texture->north_path[1], F_OK | R_OK);
			if (map->result != 0)
				error_exit("NO path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("NO path wrong");
	}
}

void	check_so(int i, t_data *map, t_texture *texture)
{
	if (ft_strncmp(map->map[i], "SO", 2) == 0)
	{
		texture->found_so++;
		if (!texture->south_path)
			texture->south_path = ft_split(map->map[i], ' ');
		if (texture->south_path[0] && texture->south_path[1] \
			&& texture->south_path[2] == NULL)
		{
			map->result = access(texture->south_path[1], F_OK | R_OK);
			if (map->result != 0)
				error_exit("SO path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("SO path wrong");
	}
}

void	check_we(int i, t_data *map, t_texture *texture)
{
	if (ft_strncmp(map->map[i], "WE", 2) == 0)
	{
		texture->found_we++;
		if (!texture->west_path)
			texture->west_path = ft_split(map->map[i], ' ');
		if (texture->west_path[0] && texture->west_path[1] && texture->west_path[2] == NULL)
		{
			map->result = access(texture->west_path[1], F_OK | R_OK);
			if (map->result != 0)
				error_exit("WE path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("WE path wrong");
	}
}

void	check_ea(int i, t_data *map, t_texture *texture)
{
	if (ft_strncmp(map->map[i], "EA", 2) == 0)
	{
		texture->found_ea++;
		if (!texture->east_path)
			texture->east_path = ft_split(map->map[i], ' ');
		if (texture->east_path[0] && texture->east_path[1] && texture->east_path[2] == NULL)
		{
			map->result = access(texture->east_path[1], F_OK | R_OK);
			if (map->result != 0)
				error_exit("EA path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("EA path wrong");
	}
}

void	check_compass_direction_in_file(int i, t_data *map, t_texture *texture)
{
	check_no(i, map, texture);
	check_so(i, map, texture);
	check_we(i, map, texture);
	check_ea(i, map, texture);
}
