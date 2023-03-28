/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:11:09 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/26 18:02:41 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dfs(t_mapData *Map, int row, int col, bool **visited)
{
	visited[row][col] = true;
	// if (Map->map[row][col] == 'C')
	// 	Map->num_collectibles--;
	if (Map->map[row][col] == '1')
		Map->found_exit = true;
	up(Map, row, col, visited);
	down(Map, row, col, visited);
	left(Map, row, col, visited);
	right(Map, row, col, visited);
}

void	up(t_mapData *Map, int row, int col, bool **visited)
{
	if (row > 0 && Map->map[row - 1][col] != '1' && !visited[row - 1][col])
		dfs(Map, row - 1, col, visited);
}

void	down(t_mapData *Map, int row, int col, bool **visited)
{
	if (row < Map->max_height - 2 \
		&& Map->map[row + 1][col] != '1' && !visited[row + 1][col])
		dfs(Map, row + 1, col, visited);
}

void	left(t_mapData *Map, int row, int col, bool **visited)
{
	if (col > 0 && Map->map[row][col - 1] != '1' && !visited[row][col - 1])
		dfs(Map, row, col - 1, visited);
}

void	right(t_mapData *Map, int row, int col, bool **visited)
{
	if (col < Map->max_width - 2 && \
		Map->map[row][col + 1] != '1' && !visited[row][col + 1])
		dfs(Map, row, col + 1, visited);
}
