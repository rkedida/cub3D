/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/28 15:12:31 by rkedida          ###   ########.fr       */
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
	free(buf);
	free(Map->line);
	close(Map->fd);
}

void	load_configuration_file(t_mapData *Map)
{
	open_file(Map);
	read_append_split_file(Map);
}
