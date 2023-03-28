/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/27 22:31:11 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_if_map_is_rectangular(t_mapData *Map)
{
	if (Map->total_cols % Map->max_height != 0)
		error_exit("Map not rectangular.");
}

bool check_surrounded_walls(t_mapData *Map)
{
	int	i;
	int	j;

	i = 0;
	while (Map->maps[i] != NULL)
	{
		j = 0;
		// printf("%s\n", Map->map[i]);
		while (Map->maps[i][j] != '\0')
		{
			if (Map->maps[i][j] == '0')
			{
				if (((i != 0 && (int)ft_strlen(Map->maps[i - 1]) > j && Map->maps[i - 1][j] == '0') || Map->maps[i - 1][j] == '1' || Map->maps[i - 1][j] == 'N' || Map->maps[i - 1][j] == 'S' || Map->maps[i - 1][j] == 'W' || Map->maps[i - 1][j] == 'E')
					&& ((Map->maps[i + 1] != NULL && (int)ft_strlen(Map->maps[i + 1]) > j && Map->maps[i + 1][j] == '0') || Map->maps[i + 1][j] == '1'|| Map->maps[i + 1][j] == 'N' || Map->maps[i + 1][j] == 'S' || Map->maps[i + 1][j] == 'W' || Map->map[i + 1][j] == 'E')
					&& ((Map->maps[i][j - 1] != '\0' && Map->maps[i][j - 1] == '0') || Map->maps[i][j - 1] == '1'|| Map->maps[i][j - 1] == 'N' || Map->maps[i][j - 1] == 'S' || Map->maps[i][j - 1] == 'W' || Map->maps[i][j - 1] == 'E')
					&& ((Map->maps[i][j + 1] != '\0' && Map->maps[i][j + 1] == '0') || Map->maps[i][j + 1] == '1'|| Map->maps[i][j + 1] == 'N' || Map->maps[i][j + 1] == 'S' || Map->maps[i][j + 1] == 'W' || Map->maps[i][j + 1] == 'E'))
				{
					j++;
					continue ;
				}
				else
					return false;
			}
			j++;
		}
		i++;
	}
	return true;
}

void	check_tracked_data(t_mapData *Map)
{
	if (Map->player == 0 || Map->num_exits == 0 || Map->num_collectibles == 0)
		error_exit("Map needs at least one Player, 1 Collectible and 1 Exit.");
}

void	check_exit_collectibles(t_mapData *Map)
{
	if (!Map->found_exit || Map->num_collectibles != 0)
		error_exit("Invalid Path in Map.");
}
