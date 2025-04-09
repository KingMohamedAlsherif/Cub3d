#include "minilibx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define PI 3.1415926535

typedef struct s_player {
    float x;
    float y;
    float angle;
    bool up, down, left, right, rot_left, rot_right;
} t_player;

typedef struct s_game {
    void *mlx;
    void *win;
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
    t_player player;
    int map[MAP_HEIGHT][MAP_WIDTH];
} t_game;

void put_pixel(t_game *game, int x, int y, int color) {
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    int index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}

void clear_screen(t_game *game) {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(game, x, y, 0x000000);
}

void init_game(t_game *game) {
    game->player.x = 2.5;
    game->player.y = 2.5;
    game->player.angle = 0;
    game->player.up = false;
    game->player.down = false;
    game->player.left = false;
    game->player.right = false;
    game->player.rot_left = false;
    game->player.rot_right = false;

    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,0,1},
        {1,0,0,0,0,1,0,1},
        {1,0,1,0,0,0,0,1},
        {1,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1}
    };
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++)
            game->map[y][x] = map[y][x];

    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Raycasting");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
}

void raycast(t_game *game) {
    float fov = PI / 3; // 60 degrees field of view
    float ray_angle_step = fov / WIDTH;

    for (int x = 0; x < WIDTH; x++) {
        float ray_angle = game->player.angle - fov / 2 + ray_angle_step * x;
        float ray_x = game->player.x;
        float ray_y = game->player.y;
        float dx = cos(ray_angle);
        float dy = sin(ray_angle);
        float distance = 0;
        bool hit = false;

        while (!hit && distance < 20) {
            distance += 0.1;
            int test_x = (int)(ray_x + dx * distance);
            int test_y = (int)(ray_y + dy * distance);

            if (test_x < 0 || test_x >= MAP_WIDTH || test_y < 0 || test_y >= MAP_HEIGHT) {
                hit = true;
            } else if (game->map[test_y][test_x] == 1) {
                hit = true;
                float wall_height = (HEIGHT / (distance * cos(ray_angle - game->player.angle))) * 2;
                int wall_top = (HEIGHT - wall_height) / 2;
                int wall_bottom = wall_top + wall_height;

                for (int y = 0; y < HEIGHT; y++) {
                    if (y < wall_top)
                        put_pixel(game, x, y, 0x87CEEB); // Sky
                    else if (y >= wall_top && y <= wall_bottom)
                        put_pixel(game, x, y, 0x808080); // Wall
                    else
                        put_pixel(game, x, y, 0x006400); // Floor
                }
            }
        }
    }
}

int key_press(int keycode, t_game *game) {
    if (keycode == 119) game->player.up = true;      // W
    if (keycode == 115) game->player.down = true;    // S
    if (keycode == 97) game->player.left = true;     // A
    if (keycode == 100) game->player.right = true;   // D
    if (keycode == 65361) game->player.rot_left = true;  // Left arrow
    if (keycode == 65363) game->player.rot_right = true; // Right arrow
    return 0;
}

int key_release(int keycode, t_game *game) {
    if (keycode == 119) game->player.up = false;
    if (keycode == 115) game->player.down = false;
    if (keycode == 97) game->player.left = false;
    if (keycode == 100) game->player.right = false;
    if (keycode == 65361) game->player.rot_left = false;
    if (keycode == 65363) game->player.rot_right = false;
    return 0;
}

void move_player(t_game *game) {
    float speed = 0.1;
    float rot_speed = 0.05;
    float new_x = game->player.x;
    float new_y = game->player.y;

    if (game->player.up) {
        new_x += cos(game->player.angle) * speed;
        new_y += sin(game->player.angle) * speed;
    }
    if (game->player.down) {
        new_x -= cos(game->player.angle) * speed;
        new_y -= sin(game->player.angle) * speed;
    }
    if (game->player.left) {
        new_x -= sin(game->player.angle) * speed;
        new_y += cos(game->player.angle) * speed;
    }
    if (game->player.right) {
        new_x += sin(game->player.angle) * speed;
        new_y -= cos(game->player.angle) * speed;
    }
    if (game->player.rot_left)
        game->player.angle -= rot_speed;
    if (game->player.rot_right)
        game->player.angle += rot_speed;

    // Simple collision detection
    if (game->map[(int)new_y][(int)new_x] == 0) {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}

int render_frame(t_game *game) {
    clear_screen(game);
    move_player(game);
    raycast(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}

int main(void) {
    t_game game;
    init_game(&game);
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game);
    mlx_loop_hook(game.mlx, render_frame, &game);
    mlx_loop(game.mlx);
    return 0;
}