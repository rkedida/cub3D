/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/28 18:22:41 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			if (ft_strchr("01NSWE ", Map->maps[i][j]))
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
	check_map_syntax(Map);
	if (check_surrounded_walls(Map) == false)
		error_exit("Map not closed");
}
