/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:12:22 by rkedida           #+#    #+#             */
/*   Updated: 2023/03/31 16:35:51 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define MAX_WINDOW_WIDTH 1920
# define MAX_WINDOW_HEIGHT 1080

typedef struct s_color
{
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
}					t_color;

typedef struct s_mapData
{
	// input Parsing
	char				*map_path;
	char				*check;
	int					result;

	// map Parsing
	int					fd;
	int					read_bytes;
	char				*line;
	char				**map;
	char				**maps;

	char				**north_path;
	char				**south_path;
	char				**west_path;
	char				**east_path;
	char				**floor;
	char				**ceiling;

	int					found_no;
	int					found_so;
	int					found_we;
	int					found_ea;
	int					found_f;
	int					found_c;

	struct s_color		*color;

	int					total_cols;
	int					max_width;
	int					max_height;
	int					cols;
	int					rows;
	int					player;
	int					num_exits;
	int					num_collectibles;
	int					max_collectibles;
	int					player_pos[2];
	int					exit_pos[2];
	bool				**visited;
	bool				found_exit;
	int					steps;
	struct s_windata	*img;
}				t_mapData;

typedef struct s_windata
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
	char	*relative_path;

	int		map_x;
	int		map_y;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}				t_winData;

// surrounded _walls.c
bool			up(t_mapData *Map, int i, int j);
bool			down(t_mapData *Map, int i, int j);
bool			left(t_mapData *Map, int i, int j);
bool			right(t_mapData *Map, int i, int j);
bool			check_surrounded_walls(t_mapData *Map);

// validate_map.c
void			check_floor_rgbs(int i, t_mapData *Map);
void			check_ceiling_rgbs(int i, t_mapData *Map);
void			validate_map(t_mapData *Map);

// compass_direction.c
void			check_no(int i, t_mapData *Map);
void			check_so(int i, t_mapData *Map);
void			check_we(int i, t_mapData *Map);
void			check_ea(int i, t_mapData *Map);
void			check_compass_direction_in_file(int i, t_mapData *Map);

// parsing_config_info.c
void			check_floor_rgbs(int i, t_mapData *Map);
void			check_ceiling_rgbs(int i, t_mapData *Map);
void			parsing_config_info(t_mapData *Map);

// load_configuration_file.c
void			open_file(t_mapData *Map);
void			ft_append(char **str, char c);
void			read_append_split_file(t_mapData *Map);
void			load_configuration_file(t_mapData *Map);

// parsing.c
void			parsing_input(t_mapData *Map, int ac, char **av);
void			parsing(int ac, char **av, t_mapData *Map);

// main.c
void			*init_map_struct(t_mapData *Map);
void			*init_windata(t_winData *img);
void			*init_color(t_color *color);

// error.c
void			error_exit(char *message);
void			*ft_malloc(void *str, size_t size);
void			ft_free(void **str);




// dfs_search.c
void			dfs(t_mapData *Map, int row, int col, bool **visited);

// key_hook_manager.c
int				handle_keypress(int keycode, t_mapData *Map);
void			move_up(t_mapData *Map);
void			move_down(t_mapData *Map);
void			move_left(t_mapData *Map);
void			move_right(t_mapData *Map);

// textures.c
void			load_images(int i, int j, t_winData *img);
void			load_texture(char c, int i, int j, t_winData *img);
void			load_textures(t_mapData *Map, t_winData *img);
int				cleanup_and_exit(t_mapData *Map);


#endif