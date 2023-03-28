/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:05 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/20 19:51:07 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_keypress(int keycode, t_mapData *Map)
{
	if (keycode == 53)
		cleanup_and_exit(Map);
	else if (keycode == 13)
		move_up(Map);
	else if (keycode == 1)
		move_down(Map);
	else if (keycode == 0)
		move_left(Map);
	else if (keycode == 2)
		move_right(Map);
	if (Map->max_collectibles == 0)
	{
		Map->map[Map->exit_pos[0]][Map->exit_pos[1]] = 'E';
		load_texture('E', Map->exit_pos[0], Map->exit_pos[1], Map->img);
	}
	return (0);
}

void	move_up(t_mapData *Map)
{
	if (Map->map[Map->player_pos[0] - 1][Map->player_pos[1]] != '1')
	{
		if (Map->map[Map->player_pos[0] - 1][Map->player_pos[1]] == 'C' \
			&& Map->max_collectibles > 0)
		{
			Map->max_collectibles--;
			Map->map[Map->player_pos[0] - 1][Map->player_pos[1]] = '0';
		}
		load_texture('0', Map->player_pos[0], Map->player_pos[1], Map->img);
		Map->player_pos[0]--;
		ft_printf("%d = Steps walked\n", ++Map->steps);
		if (Map->max_collectibles == 0 \
			&& Map->map[Map->player_pos[0]][Map->player_pos[1]] == 'E')
		{
			ft_printf("YOU WON!\n");
			cleanup_and_exit(Map);
		}
		else
			load_texture('P', Map->player_pos[0], Map->player_pos[1], Map->img);
	}
}

void	move_down(t_mapData *Map)
{
	if (Map->map[Map->player_pos[0] + 1][Map->player_pos[1]] != '1')
	{
		if (Map->map[Map->player_pos[0] + 1][Map->player_pos[1]] == 'C' \
			&& Map->max_collectibles > 0)
		{
			Map->max_collectibles--;
			Map->map[Map->player_pos[0] + 1][Map->player_pos[1]] = '0';
		}
		load_texture('0', Map->player_pos[0], Map->player_pos[1], Map->img);
		Map->player_pos[0]++;
		ft_printf("%d = Steps walked\n", ++Map->steps);
		if (Map->max_collectibles == 0 \
			&& Map->map[Map->player_pos[0]][Map->player_pos[1]] == 'E')
		{
			ft_printf("YOU WON!\n");
			cleanup_and_exit(Map);
		}
		else
			load_texture('P', Map->player_pos[0], Map->player_pos[1], Map->img);
	}
}

void	move_left(t_mapData *Map)
{
	if (Map->map[Map->player_pos[0]][Map->player_pos[1] - 1] != '1')
	{
		if (Map->map[Map->player_pos[0]][Map->player_pos[1] - 1] == 'C' \
			&& Map->max_collectibles > 0)
		{
			Map->max_collectibles--;
			Map->map[Map->player_pos[0]][Map->player_pos[1] - 1] = '0';
		}
		load_texture('0', Map->player_pos[0], Map->player_pos[1], Map->img);
		Map->player_pos[1]--;
		ft_printf("%d = Steps walked\n", ++Map->steps);
		if (Map->max_collectibles == 0 \
			&& Map->map[Map->player_pos[0]][Map->player_pos[1]] == 'E')
		{
			ft_printf("YOU WON!\n");
			cleanup_and_exit(Map);
		}
		else
			load_texture('P', Map->player_pos[0], Map->player_pos[1], Map->img);
	}
}

void	move_right(t_mapData *Map)
{
	if (Map->map[Map->player_pos[0]][Map->player_pos[1] + 1] != '1')
	{
		if (Map->map[Map->player_pos[0]][Map->player_pos[1] + 1] == 'C' \
			&& Map->max_collectibles > 0)
		{
			Map->max_collectibles--;
			Map->map[Map->player_pos[0]][Map->player_pos[1] + 1] = '0';
		}
		load_texture('0', Map->player_pos[0], Map->player_pos[1], Map->img);
		Map->player_pos[1]++;
		ft_printf("%d = Steps walked\n", ++Map->steps);
		if (Map->max_collectibles == 0 \
			&& Map->map[Map->player_pos[0]][Map->player_pos[1]] == 'E')
		{
			ft_printf("YOU WON!\n");
			cleanup_and_exit(Map);
		}
		else
			load_texture('P', Map->player_pos[0], Map->player_pos[1], Map->img);
	}
}
