/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/31 20:07:05 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_no(int i, t_mapData *Map)
{
	if (ft_strncmp(Map->map[i], "NO", 2) == 0)
	{
		Map->found_no++;
		if (!Map->north_path)
			Map->north_path = ft_split(Map->map[i], ' ');
		if (Map->north_path[0] && Map->north_path[1] \
			&& Map->north_path[2] == NULL)
		{
			Map->result = access(Map->north_path[1], F_OK | R_OK);
			if (Map->result != 0)
				error_exit("NO path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("NO path wrong");
	}
}

void	check_so(int i, t_mapData *Map)
{
	if (ft_strncmp(Map->map[i], "SO", 2) == 0)
	{
		Map->found_so++;
		if (!Map->south_path)
			Map->south_path = ft_split(Map->map[i], ' ');
		if (Map->south_path[0] && Map->south_path[1] \
			&& Map->south_path[2] == NULL)
		{
			Map->result = access(Map->south_path[1], F_OK | R_OK);
			if (Map->result != 0)
				error_exit("SO path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("SO path wrong");
	}
}

void	check_we(int i, t_mapData *Map)
{
	if (ft_strncmp(Map->map[i], "WE", 2) == 0)
	{
		Map->found_we++;
		if (!Map->west_path)
			Map->west_path = ft_split(Map->map[i], ' ');
		if (Map->west_path[0] && Map->west_path[1] && Map->west_path[2] == NULL)
		{
			Map->result = access(Map->west_path[1], F_OK | R_OK);
			if (Map->result != 0)
				error_exit("WE path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("WE path wrong");
	}
}

void	check_ea(int i, t_mapData *Map)
{
	if (ft_strncmp(Map->map[i], "EA", 2) == 0)
	{
		Map->found_ea++;
		if (!Map->east_path)
			Map->east_path = ft_split(Map->map[i], ' ');
		if (Map->east_path[0] && Map->east_path[1] && Map->east_path[2] == NULL)
		{
			Map->result = access(Map->east_path[1], F_OK | R_OK);
			if (Map->result != 0)
				error_exit("EA path doesn't exist or no Read Permissons.");
		}
		else
			error_exit("EA path wrong");
	}
}

void	check_compass_direction_in_file(int i, t_mapData *Map)
{
	check_no(i, Map);
	check_so(i, Map);
	check_we(i, Map);
	check_ea(i, Map);
}
