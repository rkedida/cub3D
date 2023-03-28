/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:18:51 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/27 23:11:11 by rkedida          ###   ########.fr       */
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
