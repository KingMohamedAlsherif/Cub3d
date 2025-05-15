/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aishamagoury <aishamagoury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:10:50 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/15 17:33:37 by aishamagour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "../cub3d.h"
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

// Structures
typedef struct s_textures
{
    char *north;
    char *south;
    char *west;
    char *east;
    void *north_img;
    void *south_img;
    void *west_img;
    void *east_img;
} t_textures;

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

typedef struct s_cub
{
    void        *mlx;
    void        *win;
    char        **rgb;
    char        **xpm;
    char        **map;
    char        **map_cpy;
    int         width;
    int         height;
    int         *color_buffer;
    int         *tex;
    double      proj_wall_h;
    int         t_size;
    int         wall_strip_height;
    int         wall_top_pixel;
    int         wall_bottom_pixel;
    char        *map_1d;
    int         map_1d_len;
    char        *c_rgb;
    char        *f_rgb;
    bool        color_flag;
    int         fd;
    int         no_pos;
    int         so_pos;
    int         we_pos;
    int         ea_pos;
    int         floor_pos;
    int         ceiling_pos;
    int         max;
    t_textures  textures;
    double      player_x;
    double      player_y;
    int         p_flag;
    double      scale_factor;
    int         fps;
    double      aim_factor;
    void        *gun;
    char        player;
    double      last_menu_action_time;
    int         rows;
    int         cols;
    int         moves;
    void        *window;
    t_color     colors;
    unsigned long floor;
    unsigned long ceiling;
}               t_cub;

// Function prototypes - removed duplicates
int     map_name(char *map);
int     check_wall(t_cub *game);
void    is_parsing(t_cub *game, char *file);
int     valid_characters(char **map, t_cub *game);
void    free_textures(t_cub *cub);
void    exit_error(t_cub *cub, char *msg);
t_cub   *textures_parsing(t_cub *cub, char *line);
int     is_texture_or_color(char *line);
int     is_valid_rgb_value(char *str);
void    assign_rgb_values(t_color *color, char **rgb, int is_floor);
void    parse_rgb(t_cub *cub, char *rgb_str, t_color *color, int is_floor);
void    assign_color(t_cub *cub, char *line, char **rgb, int *pos_flag, unsigned long *color);
void    parse_cub_file(t_cub *cub, char *filename);
void    parse_file_lines(t_cub *game, int *line_count, char ***map_lines);
void    assign_map(t_cub *game, char **map_lines, int count);
int     check_void(int i, int j, char invalid, t_cub *game);
void    free_map_lines(char **map_lines, int line_count);
void    process_map_line(t_cub *game, char ***map_lines, int *line_count, char *line);

#endif
