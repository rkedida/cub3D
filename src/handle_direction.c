/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheali <sheali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/21 00:07:42 by sheali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_north(t_data *map, t_texture *texture, int i, int j)
{
	if (check_flags(texture))
		texture->found_no++;
	else
		error_exit("Only one Player Direction allowed.");
	set_player_pos(map, i, j);
}

void	handle_south(t_data *map, t_texture *texture, int i, int j)
{
	if (check_flags(texture))
		texture->found_so++;
	else
		error_exit("Only one Player Direction allowed.");
	set_player_pos(map, i, j);
}

void	handle_west(t_data *map, t_texture *texture, int i, int j)
{
	if (check_flags(texture))
		texture->found_we++;
	else
		error_exit("Only one Player Direction allowed.");
	set_player_pos(map, i, j);
}

void	handle_east(t_data *map, t_texture *texture, int i, int j)
{
	if (check_flags(texture))
		texture->found_ea++;
	else
		error_exit("Only one Player Direction allowed.");
	set_player_pos(map, i, j);
}
