/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:12:22 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/05 22:14:04 by rkedida          ###   ########.fr       */
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
# include <time.h>
# include <float.h>
# include <stdbool.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define MAX_WINDOW_WIDTH 1920
# define MAX_WINDOW_HEIGHT 1080
# define RED 255,120,0


typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
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
	struct s_window		*win;
	struct s_img		*img;

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
}				t_data;

typedef struct s_color
{
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
	u_int32_t		color;
}					t_color;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
	
}			t_img;

typedef struct s_window
{
	int		map_x;
	int		map_y;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		tex_num;
	double	time;
	double	old_time;
	double	frame_time;
	double	move_speed;
	double	rot_speed;
	u_int32_t		buffer[MAX_WINDOW_HEIGHT][MAX_WINDOW_WIDTH];
	int		**texture;
}
				t_window;

				void move_forward(t_data *map, t_window *win);
				void move_backward(t_data *map, t_window *win);

bool mlx_verline(t_data *map, int x, int y1, int y2, int color);
int	raycaster(t_data *map, t_window *win);
double absd(double num);
void draw_buffer(t_data *map, u_int32_t buffer[MAX_WINDOW_HEIGHT][MAX_WINDOW_WIDTH]);
// void draw_buffer(t_data *map, void *mlx, void *win, int w, int h, unsigned int *buffer);
// void draw_buffer(t_data *map, void *mlx, void *win, int w, int h, unsigned int *buffer);
int	ft_mlx_pixel_put(t_data *img, int x, int y, int num_color);
// void	ft_mlx_pixel_put(t_data *mlx, int x, int y, int color);
void	move(t_data *map);
int	start_drawing(t_data *map);
void	*init_img_struct(t_img *img);

// surrounded _walls.c
bool			up(t_data *map, int i, int j);
bool			down(t_data *map, int i, int j);
bool			left(t_data *map, int i, int j);
bool			right(t_data *map, int i, int j);
bool			check_surrounded_walls(t_data *map);

// validate_map.c
void			check_floor_rgbs(int i, t_data *map);
void			check_ceiling_rgbs(int i, t_data *map);
void			validate_map(t_data *map);

// compass_direction.c
void			check_no(int i, t_data *map);
void			check_so(int i, t_data *map);
void			check_we(int i, t_data *map);
void			check_ea(int i, t_data *map);
void			check_compass_direction_in_file(int i, t_data *map);

// parsing_config_info.c
void			check_floor_rgbs(int i, t_data *map);
void			check_ceiling_rgbs(int i, t_data *map);
void			parsing_config_info(t_data *map);

// load_configuration_file.c
void			open_file(t_data *map);
void			ft_append(char **str, char c);
void			read_append_split_file(t_data *map);
void			load_configuration_file(t_data *map);

// parsing.c
void			parsing_input(t_data *map, int ac, char **av);
void			parsing(int ac, char **av, t_data *map);

// main.c
void			*init_map_struct(t_data *Map);
void			*init_window_struct(t_window *img);
void			*init_color_struct(t_color *color);

// error.c
void			error_exit(char *message);
void			*ft_malloc(void *str, size_t size);
void			ft_free(void **str);




// dfs_search.c
void			dfs(t_data *Map, int row, int col, bool **visited);

// key_hook_manager.c
int				handle_keypress(int keycode, t_data *map);
void			move_up(t_data *Map);
void			move_down(t_data *Map);
void			move_left(t_window *win);
void			move_right(t_window *win);

// textures.c
void			load_images(int i, int j, t_window *img);
void			load_texture(char c, int i, int j, t_window *img);
int			load_textures(t_data *Map, t_img *img);
int				cleanup_and_exit(t_data *map);

#endif