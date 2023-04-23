/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/23 13:59:35 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void check_floor_rgbs(int i, t_data *map, t_texture *texture)
// {
//     if (ft_strncmp(map->map[i], "F", 1) == 0)
//     {
//         texture->found_f++;
//         if (!texture->floor)
//             texture->floor = ft_split(map->map[i], ',');
//         if (texture->floor != NULL && texture->floor[0] != NULL \
//             && texture->floor[1] != NULL && texture->floor[2] != NULL \
//             && texture->floor[3] == NULL && map->color != NULL)
//         {
//             map->color->floor_r = ft_atoi(texture->floor[0] + 2);
//             map->color->floor_g = ft_atoi(texture->floor[1]);
//             map->color->floor_b = ft_atoi(texture->floor[2]);
//             if (map->color->floor_r < 0 || map->color->floor_g < 0 \
//                 || map->color->floor_b < 0)
//                 error_exit("RGB failed");
//         }
//         else
//             error_exit("Failed Floor RGB.");
//     }
// }

// void check_ceiling_rgbs(int i, t_data *map, t_texture *texture)
// {
//     if (ft_strncmp(map->map[i], "C", 1) == 0)
//     {
//         texture->found_c++;
//         if (!texture->ceiling)
//             texture->ceiling = ft_split(map->map[i], ',');
//         if (texture->ceiling != NULL && texture->ceiling[0] != NULL \
//             && texture->ceiling[1] != NULL && texture->ceiling[2] != NULL \
//             && texture->ceiling[3] == NULL && map->color != NULL)
//         {
//             map->color->ceiling_r = ft_atoi(texture->ceiling[0] + 2);
//             map->color->ceiling_g = ft_atoi(texture->ceiling[1]);
//             map->color->ceiling_b = ft_atoi(texture->ceiling[2]);
//             if (map->color->ceiling_r < 0 || map->color->ceiling_g < 0 \
//                 || map->color->ceiling_b < 0)
//                 error_exit("RGB failed");
//         }
//         else
//             error_exit("Failed Ceiling RGB.");
//     }
// }

void	check_floor_rgbs(int i, t_data *map, t_texture *texture)
{
	if (ft_strncmp(map->map[i], "F", 1) == 0)
	{
		texture->found_f++;
		if (!texture->floor)
			texture->floor = ft_split(map->map[i], ',');
		if (texture->floor != NULL && texture->floor[0] != NULL \
			&& texture->floor[1] != NULL && texture->floor[2] != NULL \
				&& texture->floor[3] == NULL)
		{
			map->color->floor_r = ft_atoi(texture->floor[0] + 2);
			map->color->floor_g = ft_atoi(texture->floor[1]);
			map->color->floor_b = ft_atoi(texture->floor[2]);
			if (map->color->floor_r < 0 || map->color->floor_r > 255 || map->color->floor_g < 0 || map->color->floor_g > 255 \
				|| map->color->floor_b < 0 || map->color->floor_b > 255)
				error_exit("RGB failed");
		}
		else
			error_exit("Failed Floor RGB.");
	}
}

void	check_ceiling_rgbs(int i, t_data *map, t_texture *texture)
{
	if (ft_strncmp(map->map[i], "C", 1) == 0)
	{
		texture->found_c++;
		if (!texture->ceiling)
			texture->ceiling = ft_split(map->map[i], ',');
		if (texture->ceiling != NULL && texture->ceiling[0] != NULL \
			&& texture->ceiling[1] != NULL && texture->ceiling[2] != NULL \
				&& texture->ceiling[3] == NULL)
		{
			map->color->ceiling_r = ft_atoi(texture->ceiling[0] + 2);
			map->color->ceiling_g = ft_atoi(texture->ceiling[1]);
			map->color->ceiling_b = ft_atoi(texture->ceiling[2]);
			if (map->color->ceiling_r < 0 || map->color->ceiling_r > 255 || map->color->ceiling_g < 0 || map->color->ceiling_g > 255 \
				|| map->color->ceiling_b < 0 || map->color->ceiling_b > 255)
				error_exit("RGB failed");
		}
		else
			error_exit("Failed Ceiling RGB.");
	}
}

// void check_floor_rgbs(int i, t_data *map, t_texture *texture)
// {
// 	char **split;

// 	if (ft_strncmp(map->map[i], "F", 1) != 0)
// 		return;

// 	texture->found_f++;

// 	split = ft_split(map->map[i], ',');
// 	if (split == NULL || split[0] == NULL || split[1] == NULL ||
// 		split[2] == NULL || split[3] != NULL)
// 		error_exit("Failed Floor RGB.");

// 	map->color->floor_r = ft_atoi(split[0] + 2);
// 	map->color->floor_g = ft_atoi(split[1]);
// 	map->color->floor_b = ft_atoi(split[2]);

// 	if (map->color->floor_r < 0 || map->color->floor_r > 255 \
// 		|| map->color->floor_g < 0 || map->color->floor_g > 255 \
// 		|| map->color->floor_b  < 0 || map->color->floor_b > 255)
// 		error_exit("RGB failed");

// 	ft_free((void **)split);
// }

// void	check_ceiling_rgbs(int i, t_data *map, t_texture *texture)
// {
// 	char **split;

// 	if (ft_strncmp(map->map[i], "C", 1) != 0)
// 		return ;

// 	texture->found_c++;

// 	split = ft_split(map->map[i], ',');
// 	if (split == NULL || split[0] == NULL \
// 			|| split[1] == NULL ||split[2] == NULL \
// 				|| split[3] != NULL)
// 		error_exit("Failed Ceiling RGB.");

// 	printf("ceiling_r: %d\n", ft_atoi(split[0] + 2));
// 	map->color->ceiling_r = ft_atoi(split[0] + 2);
// 	map->color->ceiling_g = ft_atoi(split[1]);
// 	map->color->ceiling_b = ft_atoi(split[2]);

// 	if (map->color->ceiling_r < 0 || map->color->ceiling_r > 255 \
// 		|| map->color->ceiling_g < 0 || map->color->ceiling_g > 255 \
// 		|| map->color->ceiling_b < 0 || map->color->ceiling_b > 255)
// 		error_exit("RGB failed");

// 	ft_free((void **)split);
// }

void	parsing_config_info(t_data *map, t_texture *texture)
{
	int	i;

	i = 0;
	while (map->map[i] != NULL)
	{
		printf("%s\n", map->map[i]);
		check_compass_direction_in_file(i, map, texture);
		check_floor_rgbs(i, map, texture);
		check_ceiling_rgbs(i, map, texture);
		if (texture->found_no == 1 && texture->found_so == 1 \
			&& texture->found_we == 1 && texture->found_ea == 1 \
			&& texture->found_f == 1 && texture->found_c == 1)
			break ;
		i++;
	}
	if (map->color == NULL)
		error_exit("map->color is NULL");
	if (texture->north_path == NULL && texture->south_path == NULL \
		&& texture->west_path == NULL && texture->east_path == NULL \
		&& texture->floor == NULL && texture->ceiling == NULL)
		map->maps = map->map;
	else if (texture->found_no != 1 || texture->found_so != 1 || texture->found_we != 1 \
		|| texture->found_ea != 1 || texture->found_f != 1 || texture->found_c != 1)
		error_exit("Compass Invalid Path");
	else
		map->maps = map->map + 6;
}
