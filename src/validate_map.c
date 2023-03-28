/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/27 23:29:44 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	set_exit_player_pos(t_mapData *Map)
// {
// 	Map->rows = 0;
// 	Map->cols = 0;
// 	while (Map->rows < Map->max_height)
// 	{
// 		Map->cols = 0;
// 		while (Map->cols < Map->max_width - 1)
// 		{
// 			if (Map->map[Map->rows][Map->cols] == '1')
// 			{
// 				Map->player_pos[0] = Map->rows;
// 				Map->player_pos[1] = Map->cols;
// 			}
// 			// if (Map->map[Map->rows][Map->cols] == 'E')
// 			// {
// 			// 	Map->exit_pos[0] = Map->rows;
// 			// 	Map->exit_pos[1] = Map->cols;
// 			// }
// 			Map->cols++;
// 		}
// 		Map->rows++;
// 	}
// }

// void	init_bool_visited(t_mapData *Map)
// {
// 	int		i;

// 	i = 0;
// 	Map->visited = malloc(Map->max_height * sizeof(bool *));
// 	while (i < Map->max_height)
// 	{
// 		Map->visited[i] = malloc(Map->max_width * sizeof(bool));
// 		ft_memset(Map->visited[i], false, Map->max_width * sizeof(bool));
// 		i++;
// 	}
// }

// void	validate_map(t_mapData *Map)
// {
// 	init_bool_visited(Map);
// 	set_exit_player_pos(Map);
// 	dfs(Map, Map->player_pos[0], Map->player_pos[1], Map->visited);
// 	check_exit_collectibles(Map);
// 	// ft_free((void **)Map->visited, Map);
// }

void	check_compass_direction_in_file(int i, t_mapData *Map)
{
		if (ft_strncmp(Map->map[i], "NO", 2) == 0)
		{
			Map->found_NO++;
			//  wrong
			if (!Map->north_path)
				Map->north_path = ft_split(Map->map[i], ' ');
			if (Map->north_path[0] && Map->north_path[1] && Map->north_path[2] == NULL)
			{
				Map->result = access(Map->north_path[1], F_OK);
				if (Map->result != 0)
					error_exit("NO path doesn't exist");
			}
			else
				error_exit("NO path wrong");
		}
		else if (ft_strncmp(Map->map[i], "SO", 2) == 0)
		{
			Map->found_SO++;
			if (!Map->south_path)
				Map->south_path = ft_split(Map->map[i], ' ');
			if (Map->south_path[0] && Map->south_path[1] && Map->south_path[2] == NULL)
			{
				Map->result = access(Map->south_path[1], F_OK);
				if (Map->result != 0)
					error_exit("SO path doesn't exist");
			}
			else
				error_exit("SO path wrong");
		}
		else if (ft_strncmp(Map->map[i], "WE", 2) == 0)
		{
			Map->found_WE++;
			if (!Map->west_path)
				Map->west_path = ft_split(Map->map[i], ' ');
			if (Map->west_path[0] && Map->west_path[1] && Map->west_path[2] == NULL)
			{
				Map->result = access(Map->west_path[1], F_OK);
				if (Map->result != 0)
					error_exit("WE path doesn't exist");
			}
			else
				error_exit("WE path wrong");
		}
		else if (ft_strncmp(Map->map[i], "EA", 2) == 0)
		{
			Map->found_EA++;
			if (!Map->east_path)
				Map->east_path = ft_split(Map->map[i], ' ');
			if (Map->east_path[0] && Map->east_path[1] && Map->east_path[2] == NULL)
			{
				Map->result = access(Map->east_path[1], F_OK);
				if (Map->result != 0)
					error_exit("EA path doesn't exist");
			}
			else
				error_exit("EA path wrong");
		}
}

void	check_floor_rgbs(int i, t_mapData *Map)
{
	if (ft_strncmp(Map->map[i], "F", 1) == 0)
	{
		Map->found_F++;
		if (!Map->floor)
			Map->floor = ft_split(Map->map[i], ',');
		// wrong
		if (Map->floor != NULL && Map->floor[0] != NULL && Map->floor[1] != NULL && Map->floor[2] != NULL && Map->floor[3] == NULL)
		{
			Map->color->floor_r = ft_atoi(Map->floor[0] + 2);
			Map->color->floor_g = ft_atoi(Map->floor[1]);
			Map->color->floor_b = ft_atoi(Map->floor[2]);
		}
		else
			error_exit("Failed Floor RGB.");
	}
}

void	check_ceiling_rgbs(int i, t_mapData *Map)
{
	if (ft_strncmp(Map->map[i], "C", 1) == 0)
	{
		Map->found_C++;
		if (!Map->ceiling)
			Map->ceiling = ft_split(Map->map[i], ',');
		// wrong
		if (Map->ceiling != NULL && Map->ceiling[0] != NULL && Map->ceiling[1] != NULL && Map->ceiling[2] != NULL && Map->ceiling[3] == NULL)
		{
			Map->color->ceiling_r = ft_atoi(Map->ceiling[0] + 2);
			Map->color->ceiling_g = ft_atoi(Map->ceiling[1]);
			Map->color->ceiling_b = ft_atoi(Map->ceiling[2]);
		}
		else
			error_exit("Failed Ceiling RGB.");
	}
}

void	check_map_syntax(t_mapData *Map)
{
	int	i;
	int	j;

	i = 0;
	while (Map->maps[i] != NULL)
	{
		j = 0;
		while (Map->maps[i][j] != '\0')
		{
			if (Map->maps[i][j] == ' ' || Map->maps[i][j] == '1' || Map->maps[i][j] == '0' || Map->maps[i][j] == 'N' || Map->maps[i][j] == 'S' || Map->maps[i][j] == 'W' || Map->maps[i][j] == 'E')
			{
				Map->cols++;
				Map->max_width = Map->cols;
			}
			else
				error_exit("Invalid character in Map.");
			j++;
		}
		Map->rows++;
		Map->cols = 0;
		Map->max_height = Map->rows;
		i++;
	}
}

void	validate_map(t_mapData *Map)
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
	if (Map->north_path == NULL && Map->south_path == NULL && Map->west_path == NULL && Map->east_path == NULL && Map->floor == NULL && Map->ceiling == NULL)
		Map->maps = Map->map;
	else if (Map->found_NO != 1 || Map->found_SO != 1 || Map->found_WE != 1 || Map->found_EA != 1 || Map->found_F != 1 || Map->found_C != 1)
		error_exit("Compass Invalid Path");
	else
		Map->maps = Map->map + 6;
	check_map_syntax(Map);
	if (check_surrounded_walls(Map) == false)
		error_exit("Map not closed");
	// validate_map(Map);
	
}
