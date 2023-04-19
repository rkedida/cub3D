/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:12:22 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/17 23:15:58 by rkedida          ###   ########.fr       */
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

# define MAX_WINDOW_WIDTH 5120
# define MAX_WINDOW_HEIGHT 2880
// # define RED 255,120,0


typedef struct s_data
{
	void				*mlx;
	void				*mlx_win;
	char				*map_path;
	char				*check;
	int					result;
	int					fd;
	int					read_bytes;
	char				**map;
	char				**maps;
	struct s_color		*color;
	struct s_window		*win;
	struct s_img		*img;
	struct s_texture	*texture;

}				t_data;

typedef struct s_window
{
	int					map_x;
	int					map_y;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				camera_x;
	double				raydir_x;
	double				raydir_y;
	double				sidedist_x;
	double				sidedist_y;
	double				deltadist_x;
	double				deltadist_y;
	double				perpwalldist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	int					lineheight;
	int					drawstart;
	int					drawend;
	double				wall_x;
	int					tex_x;
	int					tex_y;
	double				step;
	double				tex_pos;
	double				time;
	double				old_time;
	double				frame_time;
	double				move_speed;
	double				rot_speed;
	unsigned int		buffer[MAX_WINDOW_HEIGHT][MAX_WINDOW_WIDTH];
}				t_window;

typedef struct s_img
{
	void					*img;
	char					*addr;
	int						bpp;
	int						line_length;
	int						endian;
	int						img_width;
	int						img_height;
}			t_img;

typedef struct s_texture
{
	t_img					*north_tex;
	t_img					*south_tex;
	t_img					*west_tex;
	t_img					*east_tex;
	char					**north_path;
	char					**south_path;
	char					**west_path;
	char					**east_path;
	char					**floor;
	char					**ceiling;

	int						found_no;
	int						found_so;
	int						found_we;
	int						found_ea;
	int						found_f;
	int						found_c;
}					t_texture;

typedef struct s_color
{
	int						floor_r;
	int						floor_g;
	int						floor_b;
	int						ceiling_r;
	int						ceiling_g;
	int						ceiling_b;
	unsigned int			color;
}					t_color;

void			move_forward(t_data *map, t_window *win);
void			move_backward(t_data *map, t_window *win);
int				get_tex_pixel(t_img *texture, int x, int y);
bool			mlx_verline(t_data *map, int x, int y1, int y2, int color);
int				raycaster(t_data *map, t_window *win);
void			draw_buffer(t_data *map, \
						u_int32_t buffer[MAX_WINDOW_HEIGHT][MAX_WINDOW_WIDTH]);
void			move(t_data *map);
int				start_drawing(t_data *map);
void	ft_mlx_pixel_put(t_img *texture, int x, int y, int color);

// surrounded _walls.c
bool			up(t_data *map, int i, int j);
bool			down(t_data *map, int i, int j);
bool			left(t_data *map, int i, int j);
bool			right(t_data *map, int i, int j);
bool			check_surrounded_walls(t_data *map);

// validate_map.c
// void			check_floor_rgbs(int i, t_data *map);
// void			check_ceiling_rgbs(int i, t_data *map);
void			validate_map(t_data *map, t_texture *texture);

// compass_direction.c
void			check_no(int i, t_data *map, t_texture *texture);
void			check_so(int i, t_data *map, t_texture *texture);
void			check_we(int i, t_data *map, t_texture *texture);
void			check_ea(int i, t_data *map, t_texture *texture);
void			check_compass_direction_in_file(int i, t_data *map, t_texture *texture);

// parsing_config_info.c
void			check_floor_rgbs(int i, t_data *map, t_texture *texture);
void			check_ceiling_rgbs(int i, t_data *map, t_texture *texture);
void			parsing_config_info(t_data *map, t_texture *texture);

// load_configuration_file.c
void			open_file(t_data *map);
void			ft_append(char **str, char c);
void			read_append_split_file(t_data *map);
void			load_configuration_file(t_data *map);

// parsing.c
void			parsing_input(t_data *map, int ac, char **av);
void			parsing(int ac, char **av, t_data *map);

// main.c
t_data			*init_map_struct(void);
t_window		*init_window_struct(void);
t_img			*init_img_struct(void);
t_texture		*init_texture_struct(void);
t_color			*init_color_struct(void);
void			leaks(void);

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
void			move_left(t_window *win, t_data *map);
void			move_right(t_window *win, t_data *map);

// textures.c
void			load_images(int i, int j, t_window *img);
int				load_texture(t_data *map, char *path, t_img *img);
int				load_textures(t_data *map);
int				cleanup_and_exit(t_data *map);

#endif