/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:37:59 by amagoury          #+#    #+#             */
/*   Updated: 2025/04/17 19:42:34 by aishamagour      ###   ########.fr       */
/*   Updated: 2025/04/17 18:43:35 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
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

typedef struct s_textures
{
    char *north;
    char *south;
    char *west;
    char *east;
    void *north_img; // MLX image pointer
    void *south_img;
    void *west_img;
    void *east_img;
} t_textures;

typedef struct s_map
{
	char **map_arr;
	int map_width;
	int map_height;
	int map_st;
	int map_end;
	int wall_counter; // remove
	int plyr_counter; // remove 
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
	t_txtdata	*no;
	t_txtdata	*so;
	t_txtdata	*we;
	t_txtdata	*ea;
	int			f_arr[3];
	int			c_arr[3];
	int			f_color;
	int			c_color;
}				t_txtrs;

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
	// int m_x; // not used 
	// int m_y; // not used
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

// typedef struct s_textures
// {
// 	char    *north;
// 	char    *south;
// 	char    *west;
// 	char    *east;
// } t_textures;

typedef struct color
{
	int floor_red;
	int floor_green;
	int floor_blue;
	int ceiling_red;
	int ceiling_green;
	int ceiling_blue;
	int floor_color;
	int ceiling_color;
} t_color;
typedef struct s_game
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
} t_game;

typedef struct s_cub
{
	void				*mlx;
	void				*win;
	char				**rgb;
	char				**map;
	unsigned long		floor;
	unsigned long		ceiling;
	int   width;
    int     height;
	int					*color_buffer;
	int					*tex;
	bool				color_flag;
	int					fd;
	int					no_pos;
	int					so_pos;
	int					we_pos;
	int					ea_pos;
	t_textures          textures;
	char		player_dir;
	double player_x;
    double player_y;
	void	*window;
	char	player;
	int		rows;
	int		cols;
	int					p_flag;
	int					floor_pos;
	int					ceiling_pos;
	char				*c_rgb;
	char				*f_rgb;
}				t_cub;


// typedef struct s_gnl
// {
// 	char	*line;
// 	bool	error;
// }	t_gnl;

// typedef struct s_atoi
// {
// 	long	nbr;
// 	bool	error;
// }	t_atoi;


// ------------> UTILS FUNCTIONS <------------
// t_atoi	ft_atoi(const char *str);
int	create_rgb(int *color_arr);
void	calculate_angle(t_game *cub, char direction, int x, int y);
void	ft_free(void *address, char target);
void	use_atoi(t_game *cub, char *str_nbr, int *counter);
static void	init_malloc(t_game *cub);
static void	init_structs(t_game *cub, t_file *file, char *input_file);
static void	init_txtr(t_txtdata *txtr);
void	init(t_game *cub, char *input_file);
void	exit_failure(t_game *cub, char *err_msg);
int	exit_success(t_game *cub);


// ------------> RAYCASTING FUNCTIONS <------------
void	launch_game(t_game *cub);
void  render_color_buffer(t_game *cub);
void	project_rays(t_game *game);
int	render_loop(void *param);
void  render_map(t_game *cub);
void	turn_player(t_game *game, int direction);
void	update_player(t_game *game, double delta_x, double delta_y);
int   return_color(t_game  *cub, int   tilecolor);
void	start_the_game(t_game *cub);
int game_loop(void  *param);
void    hook(t_game  *cub, double    move_x, double  move_y);
t_map *init_argument();
void    init_player_data(t_game  cub);
int	key_reles(t_mlx_key_data keydata, t_game *cub);
int	mlx_key(t_mlx_key_data keydata, void *ml);
void    rotate_player(t_game *cub, int i);
int	check_collision(t_map *data, float new_x, float new_y);
void	move_player(t_game *cub, double move_x, double move_y);
int	inter_check(float angle, float *inter, float *step, int is_horizon);
int	wall_hit(float x, float y, t_game *cub);
float	get_h_inter(t_game *mlx, float angl);
void	shift_player(t_game *game, double delta_x, double delta_y);
float	get_v_inter(t_game *mlx, float angl);
void	cast_rays(t_game *mlx);
t_txtdata	*fetch_texture(t_game *game, int is_hori);
double	get_texture_coord(t_game *game, t_txtdata *txt, int is_hori);
void	draw_floor_ceiling(t_game *cub, int ray, int t_pix, int b_pix);
int	unit_circle(float angle, char c);
void	my_pixel_put(t_img *img, int x, int y, int color);
void	draw_wall(t_game *cub, int t_pix, int b_pix, double wall_h);
float	nor_angle(float angle);
void	render_wall(t_game *cub, int ray);
int	key_release(t_mlx_key_data keydata, t_game *game);
void    convert_parsing_to_cub3d(t_game *cub, t_cub *parsing);
void    convert_textures(t_game *cub, t_cub *parsing);

// ------------> paresing FUNCTIONS <------------
int	map_name(char *map);
int check_wall(t_cub *game);
void	is_parsing(t_cub *game, char *file);
int valid_characters(char **map, t_cub *game);
void	my_mlx_pixel_put(t_game *cub, int x, int y, int color);
void free_textures(t_cub *cub);
void exit_error(t_cub *cub, char *msg);
t_cub *textures_parsing(t_cub *cub, char *line);
void assign_color(t_cub *cub, char *line, char **rgb, int *pos_flag, unsigned long *color);
int	is_texture_or_color(char *line);
int	is_valid_rgb_value(char *str);
void assign_color(t_cub *cub, char *line, char **rgb, int *pos_flag, unsigned long *color);
char *strip_newline(char *line);
void parse_cub_file(t_cub *cub, char *filename);
void	parse_file_lines(t_cub *game, int *line_count,char ***map_lines);
void	assign_map(t_cub *game, char **map_lines, int count);
int check_void(int i, int j, char invalid, t_cub *game);
void process_map_line(t_cub *game, char ***map_lines, int *line_count, char *line);
void free_map_lines(char **map_lines, int line_count);
void	init_structs(t_game *cub, t_file *file, char *input_file);
void	init_malloc(t_game *cub);
void	init_txtr(t_txtdata *txtr);
void	init(t_game *cub, char *input_file);
int	create_rgb(int *color_arr);
void	calculate_angle(t_game *cub, char direction, int x, int y);
#endif