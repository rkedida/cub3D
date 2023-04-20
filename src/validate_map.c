/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/21 00:13:01 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_flags(t_texture *texture)
{
	if (!texture->found_no && !texture->found_so && !texture->found_we
		&& !texture->found_ea)
		return (true);
	return (false);
}

void	track_map_data(t_data *map, t_texture *texture, int i, int j)
{
	if (map->maps[i][j] == 'N')
		handle_north(map, texture, i, j);
	else if (map->maps[i][j] == 'S')
		handle_south(map, texture, i, j);
	else if (map->maps[i][j] == 'W')
		handle_west(map, texture, i, j);
	else if (map->maps[i][j] == 'E')
		handle_east(map, texture, i, j);
}

void	check_map_syntax(t_data *map, t_texture *texture)
{
	int	i;
	int	j;

	i = 0;
	texture->found_no = 0;
	texture->found_so = 0;
	texture->found_we = 0;
	texture->found_ea = 0;
	while (map->maps[i] != NULL)
	{
		j = 0;
		while (map->maps[i][j] != '\0')
		{
			if (ft_strchr("01NSWE ", map->maps[i][j]))
				track_map_data(map, texture, i, j);
			else
				error_exit("Invalid character in Map.");
			j++;
		}
		i++;
	}
	if (check_flags(texture))
		error_exit("Only one Player Direction allowed.");
}

void	validate_map(t_data *map, t_texture *texture)
{
	check_map_syntax(map, texture);
	if (check_surrounded_walls(map) == false)
		error_exit("Map not closed");
}
