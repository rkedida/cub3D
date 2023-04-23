/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surrounded_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/23 16:42:03 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	up(t_data *map, int i, int j)
{
	if ((i != 0 && (int)ft_strlen(map->maps[i - 1]) > j \
		&& map->maps[i - 1][j] == '0') || (i != 0 \
		&& (int)ft_strlen(map->maps[i - 1]) > j \
		&& map->maps[i - 1][j] == '1') || (i != 0 \
		&& (int)ft_strlen(map->maps[i - 1]) > j \
		&& map->maps[i - 1][j] == 'N') || (i != 0 \
		&& (int)ft_strlen(map->maps[i - 1]) > j \
		&& map->maps[i - 1][j] == 'S') || (i != 0 \
		&& (int)ft_strlen(map->maps[i - 1]) > j \
		&& map->maps[i - 1][j] == 'W') || (i != 0 \
		&& (int)ft_strlen(map->maps[i - 1]) > j \
		&& map->maps[i - 1][j] == 'E'))
		return (true);
	return (false);
}

bool	down(t_data *map, int i, int j)
{
	if ((map->maps[i + 1] != NULL && (int)ft_strlen(map->maps[i + 1]) > j \
		&& map->maps[i + 1][j] == '0') || (map->maps[i + 1] != NULL \
		&& map->maps[i + 1][j] == '1') || (map->maps[i + 1] != NULL \
		&& map->maps[i + 1][j] == 'N') || (map->maps[i + 1] != NULL \
		&& map->maps[i + 1][j] == 'S') || (map->maps[i + 1] != NULL \
		&& map->maps[i + 1][j] == 'W') || (map->maps[i + 1] != NULL \
		&& map->map[i + 1][j] == 'E') || (map->maps[i + 1] != NULL))
		return (true);
	return (false);
}

bool	left(t_data *map, int i, int j)
{
	if ((map->maps[i][j - 1] != '\0' && map->maps[i][j - 1] == '0') \
		|| (map->maps[i][j - 1] != '\0' && map->maps[i][j - 1] == '1') \
		|| (map->maps[i][j - 1] != '\0' && map->maps[i][j - 1] == 'N') \
		|| (map->maps[i][j - 1] != '\0' && map->maps[i][j - 1] == 'S') \
		|| (map->maps[i][j - 1] != '\0' && map->maps[i][j - 1] == 'W') \
		|| (map->maps[i][j - 1] != '\0' && map->maps[i][j - 1] == 'E'))
		return (true);	
	return (false);
}

bool	right(t_data *map, int i, int j)
{
	if ((map->maps[i][j + 1] != '\0' && map->maps[i][j + 1] == '0') \
		|| (map->maps[i][j + 1] != '\0' && map->maps[i][j + 1] == '1') \
		|| (map->maps[i][j + 1] != '\0' && map->maps[i][j + 1] == 'N') \
		|| (map->maps[i][j + 1] != '\0' && map->maps[i][j + 1] == 'S') \
		|| (map->maps[i][j + 1] != '\0' && map->maps[i][j + 1] == 'W') \
		|| (map->maps[i][j + 1] != '\0' && map->maps[i][j + 1] == 'E'))
		return (true);
	return (false);
}

bool	check_surrounded_walls(t_data *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->maps[i] != NULL)
	{
		j = 0;
		while (map->maps[i][j] != '\0')
		{
			printf("%c", map->maps[i][j]);
			if (map->maps[i][j] == '0')
			{
				if ((up(map, i, j) == true) && (down(map, i, j) == true)
					&& (left(map, i, j)) && (right(map, i, j)))
				{
					j++;
					continue ;
				}
				else
					return (false);
			}
			j++;
		}
		printf("\n");
		i++;
	}
	return (true);
}
