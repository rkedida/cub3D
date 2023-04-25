/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:12:22 by rkedida           #+#    #+#             */
/*   Updated: 2023/04/25 20:38:37 by rkedida          ###   ########.fr       */
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

# define MAX_WINDOW_WIDTH 2560
# define MAX_WINDOW_HEIGHT 1440
# define RED			0xFF0000
# define GREEN			0x00FF7F
# define BLUE			0x000080
# define CORAL			0xFF7F50
# define TURQUOISE		0x40E0D0
# define YELLOW			0xFFDB58

typedef struct s_key
{
	int					w;
	int					a;
	int					s;
	int					d;
	int					left;
	int					right;
}				t_key;

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
	struct s_key		key;
	struct s_color		*color;
	struct s_window		*win;
	struct s_img		*img;
	struct s_img		*texture_img;
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
	double				tex_pos;
	double				move_speed;
	double				rot_speed;
	unsigned int		buffer[MAX_WINDOW_HEIGHT][MAX_WINDOW_WIDTH];
	struct s_ray		*ray;
}				t_window;

typedef struct s_ray
{
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
}				t_ray;

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

// dda.c
void			update_camera_ray_direction(t_window *win, int x);
void			get_map_square(t_window *win);
void			calculate_deltadist(t_window *win);
void			calculate_sidedist(t_window *win);
void			perform_dda(t_window *win, t_data *map);

// calculate_wall_textures.c
void			calculate_wall_distance(t_window *win);
void			calculate_wall_height(t_window *win);
void			get_texture_color(t_window *win, t_data *map);
void			calculate_wall_x(t_window *win);
void			calculate_x_on_texture(t_window *win, t_data *map);

// draw.c
void			draw_floor_ceiling(t_window *win, t_data *map, int x);
int				get_tex_pixel(t_img *texture, int x, int y);
void			draw_vertical_line(t_window *win, t_data *map, int x);
void			ft_mlx_pixel_put(t_img *texture, int x, int y, int color);
void			draw_buffer(t_data *map, \
						uint32_t buffer[MAX_WINDOW_HEIGHT][MAX_WINDOW_WIDTH]);

// raycasting.c
int				rgb(int r, int g, int b, int a);
int				raycaster(t_data *map, t_window *win);
int				start_drawing(t_data *map);

// surrounded _walls.c
bool			up(t_data *map, int i, int j);
bool			down(t_data *map, int i, int j);
bool			left(t_data *map, int i, int j);
bool			right(t_data *map, int i, int j);
bool			check_surrounded_walls(t_data *map);

// direction.c
void			set_no_so(t_data *map, int i, int j);
void			set_we_ea(t_data *map, int i, int j);
void			set_player_pos(t_data *map, int i, int j);
void			check_no_so(t_data *map, t_texture *texture, int i, int j);
void			check_we_ea(t_data *map, t_texture *texture, int i, int j);

// validate_map.c
bool			check_flags(t_texture *texture);
void			track_map_data(t_data *map, t_texture *texture, int i, int j);
void			check_map_syntax(t_data *map, t_texture *texture);
void			validate_map(t_data *map, t_texture *texture);

// compass_direction.c
void			check_no(int i, t_data *map, t_texture *texture);
void			check_so(int i, t_data *map, t_texture *texture);
void			check_we(int i, t_data *map, t_texture *texture);
void			check_ea(int i, t_data *map, t_texture *texture);
void			check_compass_direction_in_file(int i, t_data *map, \
												t_texture *texture);

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

// init.c
t_data			*init_map_struct(void);
t_window		*init_window_struct(void);
t_img			*init_img_struct(void);
t_texture		*init_texture_struct(void);
t_color			*init_color_struct(void);

// main.c
void			leaks(void);

// error.c
void			error_exit(char *message);
void			*ft_malloc(void *str, size_t size);
void			ft_free(void **str);
void			turn_right(t_window *win);

// movement.c
void			move_forward(t_data *map, t_window *win);
void			move_backward(t_data *map, t_window *win);
void			move_left(t_window *win, t_data *map);
void			move_right(t_window *win, t_data *map);

// key_hook_manager.c
int				handle_keypress(int keycode, t_data *map);
int				handle_keypress_release(int keycode, t_data *map);
int				key_action(t_data *map);
void			rotate_vector(double *x, double *y, double theta);
void			turn_left(t_window *win);
void			turn_right(t_window *win);

// textures.c
int				load_texture(t_data *map, char *path, t_img *img);
int				load_textures(t_data *map);
int				load_colors(t_data *map);
void			free_textures(t_data *map);
int				cleanup_and_exit(t_data *map);

#endif