/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_configuration_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 20:17:57 by sheali           ###   ########.fr       */
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

void	check_map_rest(char *line, int k, int j)
{
	int	map_started;

	map_started = 0;
	if (line[k] == '1' || line[k] == '0')
		map_started = 1;
	while (line[k])
		k++;
	k -= 1;
	while (line[k] != '0' && line[k] != '1' && (line[k] == '\n'
			|| line[k] == '\t' || line[k] == ' '))
		k--;
	while (line[k] && line[k] != '\0')
	{
		if ((k > j) && line[k] == '\n' && line[k - 1] == '\n')
		{
			printf("Error: Double newline detected in map\n");
			exit(1);
		}
		k--;
	}
}

void	check_map_breakage(char *line)
{
	int	k;
	int	j;

	k = 0;
	if (!line[k])
	{
		printf("Error: Map is empty\n");
		exit(1);
	}
	while ((line[k] >= 32 && line[k] <= 127) || line[k] == '\n')
	{
		if (line[k] == 'C' && line[k + 1] == ' ' && (line[k + 2]
				>= 48 && line[k + 2] <= 57))
			k += 9;
		if (line[k] == 'F' && line[k + 1] == ' ' && (line[k + 2]
				>= 48 && line[k + 2] <= 57))
			k += 9;
		else if (line[k] == '1')
			break ;
		k++;
	}
	j = k;
	check_map_rest(line, k, j);
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
