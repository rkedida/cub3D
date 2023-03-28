/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/28 17:47:27 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	up(t_mapData *Map, int i, int j)
{
	if ((i != 0 && (int)ft_strlen(Map->maps[i - 1]) > j \
		&& Map->maps[i - 1][j] == '0') || (i != 0 \
		&& (int)ft_strlen(Map->maps[i - 1]) > j \
		&& Map->maps[i - 1][j] == '1') || (i != 0 \
		&& (int)ft_strlen(Map->maps[i - 1]) > j \
		&& Map->maps[i - 1][j] == 'N') || (i != 0 \
		&& (int)ft_strlen(Map->maps[i - 1]) > j \
		&& Map->maps[i - 1][j] == 'S') || (i != 0 \
		&& (int)ft_strlen(Map->maps[i - 1]) > j \
		&& Map->maps[i - 1][j] == 'W') || (i != 0 \
		&& (int)ft_strlen(Map->maps[i - 1]) > j \
		&& Map->maps[i - 1][j] == 'E'))
		return (true);
	return (false);
}

bool	down(t_mapData *Map, int i, int j)
{
	if ((Map->maps[i + 1] != NULL && (int)ft_strlen(Map->maps[i + 1]) > j \
		&& Map->maps[i + 1][j] == '0') || (Map->maps[i + 1] != NULL \
		&& Map->maps[i + 1][j] == '1') || (Map->maps[i + 1] != NULL \
		&& Map->maps[i + 1][j] == 'N') || (Map->maps[i + 1] != NULL \
		&& Map->maps[i + 1][j] == 'S') || (Map->maps[i + 1] != NULL \
		&& Map->maps[i + 1][j] == 'W') || (Map->maps[i + 1] != NULL \
		&& Map->map[i + 1][j] == 'E'))
		return (true);
	return (false);
}

bool	left(t_mapData *Map, int i, int j)
{
	if ((Map->maps[i][j - 1] != '\0' && Map->maps[i][j - 1] == '0') \
		|| (Map->maps[i][j - 1] != '\0' && Map->maps[i][j - 1] == '1') \
		|| (Map->maps[i][j - 1] != '\0' && Map->maps[i][j - 1] == 'N') \
		|| (Map->maps[i][j - 1] != '\0' && Map->maps[i][j - 1] == 'S') \
		|| (Map->maps[i][j - 1] != '\0' && Map->maps[i][j - 1] == 'W') \
		|| (Map->maps[i][j - 1] != '\0' && Map->maps[i][j - 1] == 'E'))
		return (true);
	return (false);
}

bool	right(t_mapData *Map, int i, int j)
{
	if ((Map->maps[i][j + 1] != '\0' && Map->maps[i][j + 1] == '0') \
		|| (Map->maps[i][j + 1] != '\0' && Map->maps[i][j + 1] == '1') \
		|| (Map->maps[i][j + 1] != '\0' && Map->maps[i][j + 1] == 'N') \
		|| (Map->maps[i][j + 1] != '\0' && Map->maps[i][j + 1] == 'S') \
		|| (Map->maps[i][j + 1] != '\0' && Map->maps[i][j + 1] == 'W') \
		|| (Map->maps[i][j + 1] != '\0' && Map->maps[i][j + 1] == 'E'))
		return (true);
	return (false);
}

bool	check_surrounded_walls(t_mapData *Map)
{
	int	i;
	int	j;

	i = 0;
	while (Map->maps[i] != NULL)
	{
		j = 0;
		while (Map->maps[i][j] != '\0')
		{
			if (Map->maps[i][j] == '0')
			{
				if ((up(Map, i, j) == true) && (down(Map, i, j) == true)
					&& (left(Map, i, j)) && (right(Map, i, j)))
				{
					j++;
					continue ;
				}
				else
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
