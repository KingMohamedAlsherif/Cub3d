/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:37:59 by amagoury          #+#    #+#             */
/*   Updated: 2025/04/13 16:07:53 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <fcntl.h>
# include "libft/libft.h"
# include "minilibx_opengl/mlx.h"
# include "GNL/get_next_line_bonus.h"
# include "printf/ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "includes/cons.h"
// #include "includes/colors.h"
# include "includes/keys.h"
// # include "includes/raycasting.h"
# include "includes/cons.h"
// #include "includes/shapes.h"
#include <math.h>
#include <stdbool.h>

#define S_HEIGHT 1000
#define S_WIDTH 1000
#define TILE_SIZE 30
#define FOV 60
#define ROTATE_SPEED 0.2
#define PLAYER_SPEED 4

typedef struct s_point
{
    int		x;
    int		y;
}	t_point;


// typedef struct s_cub
// {
// 	void				*mlx;
// 	void				*win;
// 	// t_img				img; // uncompleted
// 	// t_img2				img2[4];  // uncompleted
// 	char				**rgb;
// 	char				**xpm;
// 	char				**map;
// 	char				**map_cpy;
// 	unsigned long		floor;
// 	unsigned long		ceiling;
// 	// wall  checker
// 	int   width;
//     int     height;
// 	// uint32_t			texture[4][TEXTURE_HEIGHT * TEXTURE_WIDTH]; // uncompleted
// 	// t_player			player;
// 	// t_keys				keys; // uncompleted
// 	int					*color_buffer;
// 	int					*tex;
// 	double				proj_wall_h;
// 	int					t_size;
// 	int					wall_strip_height;
// 	int					wall_top_pixel;
// 	int					wall_bottom_pixel;
// 	char				*map_1d;
// 	int					map_1d_len;
// 	char				*c_rgb;
// 	char				*f_rgb;
// 	bool				color_flag;
// 	int					fd;
// 	int					no_pos;
// 	int					so_pos;
// 	int					we_pos;
// 	int					ea_pos;
// 	int					floor_pos;
// 	int					ceiling_pos;
// 	int					max;
// 	// t_dir				dir; // uncompleted
// 	int					p_flag;
// 	double				scale_factor;
// 	int					fps;
// 	double				aim_factor;
// 	void				*gun;
// 	// t_contorl_box		control_box; // uncompleted
// 	double				last_menu_action_time;
// 	// t_button_controls	button_controls; // uncompleted
// 	//check rows && cols
// 	int		rows;
// 	int		cols;
// 	// open windows
// 	int		moves;
// 	void	*window;
// }				t_cub;

// typedef struct s_textures
// {
// 	char	*north;
// 	char 	*south;
// 	char	*west;
// 	char	*east;
// }t_textures;

typedef struct s_map
{
	char **map_arr;
	int map_width;
	int map_height;
	int map_st;
	int map_end;
	int wall_counter;
	int plyr_counter;
	int p_x; // player x position in the map for testing needs delete it later
	int p_y; // player y position in the map for testing needs delete it later
	char plyr_direction;
} t_map;

typedef struct s_mlx_key_data // the mlx key data structure
{
	int key;	// the key
	int action; // the action
} mlx_key_data_t;

// typedef struct s_file
// {
// 	char **file_arr;
// 	int filepath_len;
// 	int stage;
// 	int file_len;
// } t_file;

typedef struct s_texture
{
	void *no_img;
	void *so_img;
	void *we_img;
	void *ea_img;
	int f_arr[3];
	int c_arr[3];
	int f_color;
	int c_color;
} t_texture;


typedef struct s_txtdata
{
	void *img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
	int width;
	int height;
} t_txtdata;


typedef struct s_txtrs
{
	t_txtdata *no;
	t_txtdata *so;
	t_txtdata *we;
	t_txtdata *ea;
} t_txtrs;

typedef struct s_img
{
	void *background_img;
	void *wall_img;
	void *img;
	char *addr;
	char *pixel;
	int bpp;
	int line_len;
	int endian;
	int tx_width;
	int tx_height;
} t_img;

typedef struct s_player
{
	int plyr_x;
	int plyr_y;
	double plyr_angle;
	float fov_rd;
	int rot_flag;
	int r_l;
	int u_d;
	int m_x;
	int m_y;
} t_player;

typedef struct s_ray
{
	int indx;
	double ray_angle;
	double hor_x;
	double hor_y;
	double ver_x;
	double ver_y;
	double distance;
	int wall_flag;
} t_ray;

typedef struct s_cub
{
	void *mlx_ptr;
	void *win_ptr;
	// t_file file;
	t_texture texture;
	t_map *map;
	t_player *player;
	t_img *img;
	t_ray *ray;
	t_txtrs *txtrs;
} t_cub;
;

// ------------> RAYCASTING FUNCTIONS <------------
void  render_color_buffer(t_cub *cub);
// void  init_player_pos(t_player *player);
// void  set_player(t_player *player, t_cub  *cub);
// void  init_map(t_map *map, int width, int height);
// void  set_minimap_scalefactor(t_cub *cub);
// bool  maphaswallat(double x, double y, t_player *player);
// int   get_map_at(int  i, int  j, t_player *player);
// bool  is_inside_map(double x, double y, t_player *player);
void  render_map(t_cub *cub);
int   return_color(t_cub  *cub, int   tilecolor);

// ------------> paresing FUNCTIONS <------------
int	map_name(char *map);
void	get_map(char *read_map, t_cub *game);
char	**get_map_from_file(char *read_map, t_cub *game);
int	check_wall(t_cub *game);
void	is_parsing(t_cub *game, char *file);

#endif
