/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:37:59 by amagoury          #+#    #+#             */
/*   Updated: 2025/04/17 19:42:34 by aishamagour      ###   ########.fr       */
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
#include <math.h>
#include <stdbool.h>

# define M_PI 3.14159265358979323846
# define ON_DESTROY 17
# define MLX_KEY_ESCAPE 53
# define MLX_KEY_W 13
# define MLX_KEY_A 0
# define MLX_KEY_S 1
# define MLX_KEY_D 2
# define MLX_KEY_LEFT 123
# define MLX_KEY_RIGHT 124
# define MLX_PRESS 2
# define MLX_RELEASE 3
# define MLX_REPEAT 1



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

typedef struct s_map
{
	char **map_arr;
	int map_width;
	int map_height;
	int map_st;
	int map_end;
	int wall_counter;
	int plyr_counter;
	int p_x; 
	int p_y; 
	char plyr_direction;
} t_map;

typedef struct s_mlx_key_data // the mlx key data structure
{
	int key;	// the key
	int action; // the action
} t_mlx_key_data;

typedef struct s_file
{
	char **file_arr;
	int filepath_len;
	int stage;
	int file_len;
} t_file;

typedef struct s_txtrs
{
	t_txtdata	*no;
	t_txtdata	*so;
	t_txtdata	*we;
	t_txtdata	*ea;
	int			f_arr[3];
	int			c_arr[3];
	int			f_color;
	int			c_color;
}				t_txtrs;


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
	t_file file;
	t_txtrs texture;
	t_map *map;
	t_player *player;
	t_img *img;
	t_ray *ray;
	t_txtrs *txtrs;
} t_cub;

typedef struct s_gnl
{
	char	*line;
	bool	error;
}	t_gnl;

typedef struct s_atoi
{
	long	nbr;
	bool	error;
}	t_atoi;


// ------------> UTILS FUNCTIONS <------------
t_atoi	ft_atoi(const char *str);
int	create_rgb(int *color_arr);
void	calculate_angle(t_cub *cub, char direction, int x, int y);
void	ft_free(void **ptr, char type);
void	use_atoi(t_cub *cub, char *str_nbr, int *counter);
static void	init_malloc(t_cub *cub);
static void	init_structs(t_cub *cub, t_file *file, char *input_file);
static void	init_txtr(t_txtdata *txtr);
void	init(t_cub *cub, char *input_file);
void	exit_failure(t_cub *cub, char *err_msg);
int	exit_success(t_cub *cub);

// ------------> RAYCASTING FUNCTIONS <------------
void  render_color_buffer(t_cub *cub);
void  render_map(t_cub *cub);
int   return_color(t_cub  *cub, int   tilecolor);
void	start_the_game(t_cub *cub);
int game_loop(void  *param);
void    hook(t_cub  *cub, double    move_x, double  move_y);
t_map *init_argument();
void    init_player_data(t_cub  cub);
int	key_reles(t_mlx_key_data keydata, t_cub *cub);
int	mlx_key(t_mlx_key_data keydata, void *ml);
void    rotate_player(t_cub *cub, int i);
int	check_collision(t_map *data, float new_x, float new_y);
void	move_player(t_cub *cub, double move_x, double move_y);
int	inter_check(float angle, float *inter, float *step, int is_horizon);
int	wall_hit(float x, float y, t_cub *cub);
float	get_h_inter(t_cub *mlx, float angl);
float	get_v_inter(t_cub *mlx, float angl);
void	cast_rays(t_cub *mlx);
t_txtdata	*get_txt(t_cub *cub, int flag);
double	texture_x(t_cub *cub, t_txtdata *texture, int flag);
void	draw_floor_ceiling(t_cub *cub, int ray, int t_pix, int b_pix);
int	unit_circle(float angle, char c);
void	my_pixel_put(t_img *img, int x, int y, int color);
void	draw_wall(t_cub *cub, int t_pix, int b_pix, double wall_h);
float	nor_angle(float angle);
void	render_wall(t_cub *cub, int ray);
int	key_release(t_mlx_key_data keydata, t_cub *game);


// ------------> paresing FUNCTIONS <------------
int	map_name(char *map);
void	get_map(char *read_map, t_cub *game);
char	**get_map_from_file(char *read_map, t_cub *game);
int	check_wall(t_cub *game);
void	is_parsing(t_cub *game, char *file);
void	parsing(t_cub *cub, char *input_file);


#endif
