/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_configuration_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/04 00:54:43 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_file(t_data *map)
{
	map->fd = open(map->map_path, O_RDONLY);
	if (map->fd == -1)
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

void	read_append_split_file(t_data *map)
{
	char		*buf;

	buf = NULL;
	buf = ft_malloc(buf, 1);
	map->line = ft_malloc(map->line, 1);
	map->read_bytes = read(map->fd, buf, 1);
	while (map->read_bytes > 0)
	{
		ft_append(&(map->line), buf[0]);
		map->read_bytes = read(map->fd, buf, 1);
	}
	map->map = ft_split(map->line, '\n');
	free(buf);
	free(map->line);
	close(map->fd);
}

void	load_configuration_file(t_data *map)
{
	open_file(map);
	read_append_split_file(map);
}
