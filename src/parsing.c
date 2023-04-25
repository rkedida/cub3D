/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 21:44:19 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_textures(t_data *map)
{
	if (map->texture->north_tex != NULL)
		free(map->texture->north_tex);
	if (map->texture->south_tex != NULL)
		free(map->texture->south_tex);
	if (map->texture->west_tex != NULL)
		free(map->texture->west_tex);
	if (map->texture->east_tex != NULL)
		free(map->texture->east_tex);
	if (map->texture->north_path != NULL)
		ft_free((void **)map->texture->north_path);
	if (map->texture->south_path != NULL)
		ft_free((void **)map->texture->south_path);
	if (map->texture->west_path != NULL)
		ft_free((void **)map->texture->west_path);
	if (map->texture->east_path != NULL)
		ft_free((void **)map->texture->east_path);
	if (map->texture->floor != NULL)
		ft_free((void **)map->texture->floor);
	if (map->texture->ceiling != NULL)
		ft_free((void **)map->texture->ceiling);
}

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

void	load_configuration_file(t_data *map)
{
	open_file(map);
	read_append_split_file(map);
}

void	parsing(int ac, char **av, t_data *map)
{
	parsing_input(map, ac, av);
	load_configuration_file(map);
	parsing_config_info(map, map->texture);
	validate_map(map, map->texture);
}
