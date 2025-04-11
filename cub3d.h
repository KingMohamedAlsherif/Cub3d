/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:37:59 by amagoury          #+#    #+#             */
/*   Updated: 2025/04/11 17:16:52 by malsheri         ###   ########.fr       */
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
#include "includes/colors.h"
# include "includes/keys.h"
# include "includes/raycasting.h"
# include "includes/cons.h"
#include "includes/shapes.h"
#include <math.h>
#include <stdbool.h>

typedef struct s_point
{
    int		x;
    int		y;
}	t_point;


typedef struct s_cub
{
	void				*mlx;
	void				*win;
	// t_img				img; // uncompleted
	// t_img2				img2[4];  // uncompleted
	char				**rgb;
	char				**xpm;
	char				**map;
	char				**map_cpy;
	unsigned long		floor;
	unsigned long		ceiling;
	// wall  checker
	int   width;
    int     height;
	// uint32_t			texture[4][TEXTURE_HEIGHT * TEXTURE_WIDTH]; // uncompleted
	// t_player			player;
	// t_keys				keys; // uncompleted
	int					*color_buffer;
	int					*tex;
	double				proj_wall_h;
	int					t_size;
	int					wall_strip_height;
	int					wall_top_pixel;
	int					wall_bottom_pixel;
	char				*map_1d;
	int					map_1d_len;
	char				*c_rgb;
	char				*f_rgb;
	bool				color_flag;
	int					fd;
	int					no_pos;
	int					so_pos;
	int					we_pos;
	int					ea_pos;
	int					floor_pos;
	int					ceiling_pos;
	int					max;
	// t_dir				dir; // uncompleted
	int					p_flag;
	double				scale_factor;
	int					fps;
	double				aim_factor;
	void				*gun;
	// t_contorl_box		control_box; // uncompleted
	double				last_menu_action_time;
	// t_button_controls	button_controls; // uncompleted
	//check rows && cols
	int		rows;
	int		cols;
	// open windows
	int		moves;
	void	*window;
}				t_cub;

typedef struct s_textures
{
	char	*north;
	char 	*south;
	char	*west;
	char	*east;
}t_textures;




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
