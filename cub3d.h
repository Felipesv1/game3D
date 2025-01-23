/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontes <fmontes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:40:20 by felperei          #+#    #+#             */
/*   Updated: 2025/01/23 15:03:28 by fmontes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../../minilibx/mlx.h"
# include "../../minilibx/mlx_int.h"
# include "./libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# define ESC 65307
# define KEY_A 97
# define KEY_W 119
# define KEY_D 100
# define KEY_S 115
# define KEY_Q 113
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define S_W 1920
# define S_H 1015
# define ROTATION_SPEED 0.2
# define PLAYER_SPEED 0.3
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

typedef struct s_player
{
	double		plyr_x;
	double		plyr_y;
	int			n_player;
}				t_player;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_ray;

typedef struct s_texture
{
	void		*ptr;
	int			w;
	int			h;

}				t_texture;

typedef struct s_textures
{
	t_texture	*north;
	t_texture	*west;
	t_texture	*east;
	t_texture	*south;

}				t_textures;

typedef struct s_map_texture
{
	char		*text_no;
	char		*text_so;
	char		*text_we;
	char		*text_ea;
	char		*floor;
	char		*ceiling;
	int			f;
	int			c;
}				t_map_texture;

typedef struct s_data
{
	char			**backup;
	char			**map2d;
	char			**map_copy;
	int				p_x;
	int				p_y;
	int				w_map;
	int				h_map;
	double			p_dir_x;
	double			p_dir_y;
	double			plane_x;
	double			plane_y;
	int				draw_start;
	int				draw_end;
	int				line_height;
	int				tex_x;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	char			*data;
	int				rows;
	int				cols;
	char			**textu;
	char			**c_flor;
	t_map_texture	*map_texts;
}				t_data;

typedef struct s_raycast
{
	double		raydir_x;
	double		raydir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		pos_x;
	double		pos_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}				t_raycast;

typedef struct s_mlx
{
	void		*mlx_p;
	void		*win;
	void		*img_ptr;
	t_player	*ply;
	t_ray		*ray;
	t_textures	*textures;

	t_data		*dt;
	t_raycast	*rc;
}				t_mlx;

// MAP
int				ft_exit(t_mlx *mlx);
char			**read_map(char *path);
char			**get_map(char **path);
int				**copy_map(char **map, t_data *dt);
void			size_map(t_data *dt);
void			update_map(t_mlx *mlx);
int				**copy_char_to_int(char **map, t_data *dt);
void			validate_map(char **map, t_mlx mlx);
void			is_format_valid(char *av, t_mlx mlx);

// PLAYER

void			move_player_forward(t_mlx *mlx);
void			move_player_backward(t_mlx *mlx);
void			rotate_player(t_mlx *mlx, int i);
int				keypress(int keycode, t_mlx *game);
void			game_events(int keycode, t_mlx *game);
void			find_player(t_mlx *mlx);

// RAYCASTING

void			draw_buffer(t_mlx *mlx, int x);
int				get_texture_color(t_mlx *mlx, int x, int y);
void			calculate_step_and_side_dist(t_raycast *rc, int mapX, int mapY);
void			perform_dda(int *mapX, int *mapY, t_raycast *rc, t_mlx *mlx);
double			calculate_perp_wall_dist(int mapX, int mapY, t_raycast *rc);
void			calculate_line_height(t_mlx *mlx, double perp_wall_dist);
void			raycasting(t_mlx *mlx);

// TEXTURES

void			get_textures(t_data *data);
void			get_floor_ceiling(t_data *data);
int				rgb_to_hex(char *texture);

// UTILS
void			cleanup(t_mlx *mlx);
void			initialize_graphics(t_mlx *mlx);
void			load_textures(t_mlx *mlx, int *i, int *j);
void			initialize_mlx_structures(t_mlx *mlx);
int				check_path(char *path);
void			validate_path(t_mlx mlx);
void			is_valid_rgb(char *str, t_mlx mlx);
void			free_matrix(char **matrix);
#endif

// SET DIRECTIONS 
void			set_direction_north(t_mlx *mlx);
void			set_direction_south(t_mlx *mlx);
void			set_direction_east(t_mlx *mlx);
void			set_direction_west(t_mlx *mlx);
void			handle_player_direction(t_mlx *mlx, int x, int y);