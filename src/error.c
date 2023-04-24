/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:18:51 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/24 14:23:19 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	error_exit(char *message)
{
	if (message)
	{
		write(2, "Error: ", 7);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	else
	{
		write(2, "Error: UNKNOWN", 14);
		exit(EXIT_FAILURE);
	}
}

void	error_prints(void *mlx, int num)
{
	static const char	*errors[] = {A, B};

	if (!mlx)
	{
		exit(EXIT_FAILURE);
		write (2, errors[num - 1], ft_strlen(errors[num - 1]));
	}
}

void	*ft_malloc(void *str, size_t size)
{
	str = malloc(size);
	if (!str)
		error_exit("malloc failed.");
	return (str);
}

void	ft_free(void **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_map(t_data *map)
{
	free(map->texture);
	free(map->win);
	free(map->color);
	ft_free((void **)map->map);
	map->texture = NULL;
	map->win = NULL;
	map->color = NULL;
	map->map = NULL;
}
