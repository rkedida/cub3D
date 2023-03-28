/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/27 23:29:32 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_file(t_mapData *Map)
{
	Map->fd = open(Map->map_path, O_RDONLY);
	if (Map->fd == -1)
		error_exit("Error opening file.");
}

void	ft_append(char **str, char c)
{
	char	*new_str;
	int		len;

	new_str = NULL;
	len = 0;
	if (!str)
		return ;
	len = ft_strlen(*str);
	new_str = ft_malloc(new_str, (len + 2));
	ft_memcpy(new_str, *str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(*str);
	*str = new_str;
}

void	read_append_split_file(t_mapData *Map)
{
	char		*buf;

	buf = NULL;	
	buf = ft_malloc(buf, 1);
	Map->line = ft_malloc(Map->line, 1);
	Map->read_bytes = read(Map->fd, buf, 1);
	while (Map->read_bytes > 0)
	{
		ft_append(&(Map->line), buf[0]);
		Map->read_bytes = read(Map->fd, buf, 1);
	}
	Map->map = ft_split(Map->line, '\n');
	// Map->maps = Map->map + 6;
	free(buf);
	free(Map->line);
	close(Map->fd);
}


void	check_if_null(char *str)
{
	if (str == NULL)
		error_exit("STR Compass Invalid Path.");
}



void	parsing_map(t_mapData *Map)
{
	open_file(Map);
	read_append_split_file(Map);
	validate_map(Map);
	for(int i = 0; Map->map[i] != NULL; i++)
	{
		// Map->line = Map->map[i];
		printf("%s\n", Map->map[i]);
	}

	printf("============================================================\n");
	
	// printf("%s\n", Map->north_path);
	// printf("%s\n", Map->south_path);
	// printf("%s\n", Map->west_path);
	// printf("%s\n", Map->east_path);
	printf("floor x = %d, floor y = %d, floor z = %d\n", Map->color->floor_r, Map->color->floor_g, Map->color->floor_b);
	printf("ceiling x = %d, ceiling y = %d, ceiling z = %d\n", Map->color->ceiling_r, Map->color->ceiling_g, Map->color->ceiling_b);
	printf("%d - rows === %d - cols\n", Map->rows, Map->max_width);

	for (int i = 0; Map->maps[i] != NULL; i++)
	{
		printf("%s\n", Map->maps[i]);
	}
	// printf("%s\n", Map->floor[0]);
	// printf("%s\n", Map->line);
	// printf("%s\n", Map->ceiling);
	// check_if_map_is_rectangular(Map);
	// check_surrounded_walls(Map);
	// check_tracked_data(Map);
}
// void	parsing_map(t_mapData *Map)
// {
// 	char		*buf;

// 	buf = NULL;
// 	open_file(Map);
// 	buf = ft_malloc(buf, 1);
// 	Map->line = ft_malloc(Map->line, 1);
// 	Map->read_bytes = read(Map->fd, buf, 1);
// 	while (Map->read_bytes > 0)
// 	{
// 		read_validate_append(buf[0], Map);
// 		Map->read_bytes = read(Map->fd, buf, 1);
// 	}
// 	check_if_map_is_rectangular(Map);
// 	Map->map = ft_split(Map->line, '\n');
// 	check_surrounded_walls(Map);
// 	check_tracked_data(Map);
// 	free(buf);
// 	free(Map->line);
// 	close(Map->fd);
// }
