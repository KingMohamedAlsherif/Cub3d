#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>



// Constants
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define FOV (M_PI / 3)
#define MOVE_SPEED 0.1
#define ROTATE_SPEED 0.05

// Game state
typedef struct s_data {
    void *mlx;
    void *win;
    double player_x;
    double player_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_data;

// Map (1 = wall, 0 = empty)
int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Handle keyboard input
int key_hook(int keycode, t_data *data) {
    if (keycode == 53) // Escape
        exit(0);
    if (keycode == 13) { // Up arrow/W
        if (map[(int)(data->player_y + data->dir_y * MOVE_SPEED)][(int)data->player_x] == 0)
            data->player_y += data->dir_y * MOVE_SPEED;
        if (map[(int)data->player_y][(int)(data->player_x + data->dir_x * MOVE_SPEED)] == 0)
            data->player_x += data->dir_x * MOVE_SPEED;
    }
    if (keycode == 1) { // Down arrow/S
        if (map[(int)(data->player_y - data->dir_y * MOVE_SPEED)][(int)data->player_x] == 0)
            data->player_y -= data->dir_y * MOVE_SPEED;
        if (map[(int)data->player_y][(int)(data->player_x - data->dir_x * MOVE_SPEED)] == 0)
            data->player_x -= data->dir_x * MOVE_SPEED;
    }
    if (keycode == 0) { // Left arrow/A
        double old_dir_x = data->dir_x;
        data->dir_x = data->dir_x * cos(-ROTATE_SPEED) - data->dir_y * sin(-ROTATE_SPEED);
        data->dir_y = old_dir_x * sin(-ROTATE_SPEED) + data->dir_y * cos(-ROTATE_SPEED);
        double old_plane_x = data->plane_x;
        data->plane_x = data->plane_x * cos(-ROTATE_SPEED) - data->plane_y * sin(-ROTATE_SPEED);
        data->plane_y = old_plane_x * sin(-ROTATE_SPEED) + data->plane_y * cos(-ROTATE_SPEED);
    }
    if (keycode == 2) { // Right arrow/D
        double old_dir_x = data->dir_x;
        data->dir_x = data->dir_x * cos(ROTATE_SPEED) - data->dir_y * sin(ROTATE_SPEED);
        data->dir_y = old_dir_x * sin(ROTATE_SPEED) + data->dir_y * cos(ROTATE_SPEED);
        double old_plane_x = data->plane_x;
        data->plane_x = data->plane_x * cos(ROTATE_SPEED) - data->plane_y * sin(ROTATE_SPEED);
        data->plane_y = old_plane_x * sin(ROTATE_SPEED) + data->plane_y * cos(ROTATE_SPEED);
    }
    return 0;
}

// Render function (adjusted to match mlx_loop_hook's expected signature)
int render(t_data *data) {
    // Clear screen
    mlx_clear_window(data->mlx, data->win);
    
    // Draw ceiling and floor
    int x, y;
    for (y = 0; y < WIN_HEIGHT / 2; y++) {
        for (x = 0; x < WIN_WIDTH; x++) {
            mlx_pixel_put(data->mlx, data->win, x, y, 0x444444);
        }
    }
    for (y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++) {
        for (x = 0; x < WIN_WIDTH; x++) {
            mlx_pixel_put(data->mlx, data->win, x, y, 0x666666);
        }
    }
    
    // Ray casting
    for (x = 0; x < WIN_WIDTH; x++) {
        double camera_x = 2 * x / (double)WIN_WIDTH - 1; // X coordinate in camera space
        double ray_dir_x = data->dir_x + data->plane_x * camera_x;
        double ray_dir_y = data->dir_y + data->plane_y * camera_x;
        
        int map_x = (int)data->player_x;
        int map_y = (int)data->player_y;
        
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        
        double side_dist_x = (data->player_x - map_x) * delta_dist_x;
        double side_dist_y = (data->player_y - map_y) * delta_dist_y;
        
        int step_x = ray_dir_x > 0 ? 1 : -1;
        int step_y = ray_dir_y > 0 ? 1 : -1;
        
        int hit = 0;
        int side;
        
        while (!hit) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            
            if (map[map_y][map_x] == 1)
                hit = 1;
        }
        
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - data->player_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - data->player_y + (1 - step_y) / 2) / ray_dir_y;
        
        int line_height = abs((int)(WIN_HEIGHT / perp_wall_dist));
        int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
        int draw_end = line_height / 2 + WIN_HEIGHT / 2;
        
        if (draw_start < 0)
            draw_start = 0;
        if (draw_end >= WIN_HEIGHT)
            draw_end = WIN_HEIGHT - 1;
        
        // Draw the wall
        for (y = draw_start; y < draw_end; y++) {
            mlx_pixel_put(data->mlx, data->win, x, y, side == 0 ? 0x888888 : 0x666666);
        }
    }
    
    return 0; // Return an integer to match the expected function signature
}

// Main loop
int main() {
    t_data data;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Ray Casting Test");
    
    // Initialize player
    data.player_x = 1.5;
    data.player_y = 1.5;
    data.dir_x = 1;
    data.dir_y = 0;
    data.plane_x = 0;
    data.plane_y = 0.66;
    
    // Hook keyboard and render functions
    mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
    mlx_loop_hook(data.mlx, render, &data); // Pass the function pointer correctly
    
    mlx_loop(data.mlx);
    return 0;
}