/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/06 17:13:32 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parsing_input(t_data *map, int ac, char **av)
{
	if (ac != 2)
		error_exit("usage: ./cub3D maps/...");
	else if (av[1])
	{
		map->map_path = av[1];
		map->check = ft_strchr(map->map_path, '.');
		if (ft_strcmp(map->map_path + (ft_strlen(av[1]) - 4), ".cub") != 0)
			error_exit("is not a Valid map file.");
		else if (ft_strlen(map->check) > 4)
			error_exit("is not a Valid map file.");
		map->result = access(map->map_path, F_OK);
		if (map->result != 0)
			error_exit("File doesn't exist.");
		map->result = access(map->map_path, R_OK);
		if (map->result != 0)
			error_exit("You don't have read permissons for the file.");
	}
}

void	parsing(int ac, char **av, t_data *map)
{
	parsing_input(map, ac, av);
	load_configuration_file(map);
	parsing_config_info(map);
	// validate_map(map);
}
