/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/31 22:14:16 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_flags(t_mapData *Map)
{
	if (!Map->found_no && !Map->found_so && !Map->found_we && !Map->found_ea)
		return (true);
	// else
	// 	error_exit("Only one Player Direction allowed.");
	return (false);
}

void	set_player_pos(t_mapData *Map, int i, int j)
{
		Map->player_pos[0] = i;
		Map->player_pos[1] = j;
}

void	track_map_data(t_mapData *Map, int i, int j)
{
	if (Map->maps[i][j] == 'N')
	{
		if (check_flags(Map))
			Map->found_no++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(Map, i, j);
	}
	else if (Map->maps[i][j] == 'S')
	{
		if (check_flags(Map))
			Map->found_so++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(Map, i, j);
	}
	else if (Map->maps[i][j] == 'W')
	{
		if (check_flags(Map))
			Map->found_we++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(Map, i, j);
	}
	else if (Map->maps[i][j] == 'E')
	{
		if (check_flags(Map))
			Map->found_ea++;
		else
			error_exit("Only one Player Direction allowed.");
		set_player_pos(Map, i, j);
	}
}

void	check_map_syntax(t_mapData *Map)
{
	int	i;
	int	j;

	i = 0;
	Map->found_no = 0;
	Map->found_so = 0;
	Map->found_we = 0;
	Map->found_ea = 0;
	while (Map->maps[i] != NULL)
	{
		j = 0;
		while (Map->maps[i][j] != '\0')
		{
			if (ft_strchr("01NSWE ", Map->maps[i][j]))
				track_map_data(Map, i, j);
			else
				error_exit("Invalid character in Map.");
			j++;
		}
		i++;
	}
	if (check_flags(Map))
		error_exit("Only one Player Direction allowed.");
}

void	validate_map(t_mapData *Map)
{
	if (check_surrounded_walls(Map) == false)
		error_exit("Map not closed");
	check_map_syntax(Map);
	printf("%d - rows ==== %d - cols\n", Map->player_pos[0], Map->player_pos[1]);
}
