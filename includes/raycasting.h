#ifndef RAYCASTING_H
#define RAYCASTING_H


# define TILE_SIZE 64
#include "../cub3d.h"
#include <stdbool.h>

typedef struct s_ray {
    t_point  h_wallhit;
    t_point  v_wallhit;
    t_point  h_intercept;
    t_point  v_intercept;
    t_point  h_step;
    t_point  v_step;
    t_point  next_h_touch;
    t_point  next_v_touch;
    t_point  check;
    t_point  wallhit;
    double  ray_angle;
    double  h_dist;
    double  v_dist;
    double  dist;
    bool    hitvertical;
    bool    ray_facing_up;
    bool    ray_facing_down;
    bool    ray_facing_left;
    bool    ray_facing_right;
    bool    found_h_hit;
    bool    found_v_hit;
    int     wallhit_content;
    int     horz_wall_content;
    int     vert_wall_content;
    int     stripid;
    double  correct_dist;
}   t_ray;

typedef struct s_map {
    char    **map;
    // int   width;
    // int     height;
    double  x_scale_factor;
    double  y_scale_factor;
    double  small_factor;
    double  big_factor;
    int     map_bg_color;
    int     map_wall_color;
    int     map_ray_color;
}   t_map;


typedef struct s_player {
    t_point  pos;
    t_circle  circle;
    t_rect  rect;
    t_point  l_start;
    t_point  l_end;
    int      radius;
    float     width;
    float     height;
    int      turn_dir;
    int      walk_dir;
    float     r_angle;
    float     turn_speed;
    float     walk_speed;
    t_ray    rays[NUM_RAYS];
    t_map    map3d;
    double   dist_proj_plane;
    double   mid_ray;
    double   fov;
}   t_player;

#endif