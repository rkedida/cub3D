/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_configuration_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 07:10:50 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_file(t_data *map)
{
	map->fd = open(map->map_path, O_RDONLY);
	if (map->fd == -1)
		error_exit("Error opening file.");
}

void	check_map_breakage(char *line)
{
	int	k;

	k = 0;
	if (!line[k])
		error_exit("Empty map file");
	while (line[k])
	{
		if (line[k] == '\n' && line[k - 1] == '\n')
			error_exit("Map file is broken");
		k++;
	}
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

void	read_append_split_file(t_data *map)
{
	char		*buf;
	char		*line;

	buf = NULL;
	line = NULL;
	buf = ft_malloc(buf, 1);
	line = ft_malloc(line, 1);
	map->read_bytes = read(map->fd, buf, 1);
	while (map->read_bytes > 0)
	{
		ft_append(&line, buf[0]);
		map->read_bytes = read(map->fd, buf, 1);
	}
	check_map_breakage(line);
	map->map = ft_split(line, '\n');
	free(buf);
	free(line);
	close(map->fd);
}

void	load_configuration_file(t_data *map)
{
	open_file(map);
	read_append_split_file(map);
}
