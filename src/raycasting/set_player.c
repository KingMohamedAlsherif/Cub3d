/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:39:28 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/09 16:52:09 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void  render_color_buffer(t_cub *cub)
{
    int x;
    int y;

    x = -1;
    while (++x < WINDOW_WIDTH)
    {
        y = -1;
        while(++y < WINDOW_HEIGHT)
        {
            my_mlx_put_pixel(&cub->img, x, y, cub->color_buffer[(WINDOW_WIDTH * y) + x]);
        }
    }
}

void    init_player_pos(t_player *player)
{
    int x;
    int y;
    int new_x;
    int new_y;

    y = -1;
    while (++y < player->map3d.height)
    {
        x = -1;
        while (++x < player->map3d.width)
        {
            if (player->map3d.map[y][x] == 'N' || player->map3d.map[y][x] == 'S' ||
                player->map3d.map[y][x] == 'E' || player->map3d.map[y][x] == 'W')
            {
                new_x = x;
                new_y = y;
                player->map3d.map[y][x] = '0';
            }
        }
    }
    init_point(&player->pos, ((new_x * TILE_SIZE) + (TILE_SIZE / 2)), ((new_y * TILE_SIZE) + (TILE_SIZE / 2)));
}

void    set_player(t_player *player, t_cub  *cub)
{
    init_player_pos(player);
    player->width = 3;
    player->height = 3;
    player->turn_dir = 0;
    player->walk_dir = 0;
    player->r_angle = cub->dir.actual_dir; // UNCOMPLETED
    player->walk_speed = 3;
    player->turn_speed = (1.5 * cub->fbs) * (PI / 180); // UNCOMPLETED
    player->radius = 10;
}

void    init_map(t_cub  *cub)
{
    cub->player.map3d.map = cub->map.map;
    cub->player.map3d.height = return_split_len(cub->map);
    cub->player.map3d.width = ft_strlen(cub->map.map[0]);
    cub->player.map3d.map_bg_color = DARK_BLUE_COLOR;
    cub->player.map3d.map_wall_color = LIGHT_BLUE_COLOR;
    cub->player.map3d.map_ray_color = BRIGHT_YELLOW;
}

void set_minimap_scalefactor(t_cub *cub) {
    double mini_width;
    double mini_height;
    t_map *mini_map;

    mini_map = &cub->player.map3d;
    mini_map->x_scale_factor = (mini_map->width * TILE_SIZE);
    mini_map->y_scale_factor = (mini_map->height * TILE_SIZE);
    mini_width = (WINDOW_WIDTH / mini_map->x_scale_factor) * cub->scale_factor;
    mini_height = (WINDOW_HEIGHT / mini_map->y_scale_factor) * cub->scale_factor;
    mini_map->x_scale_factor = mini_width;
    mini_map->y_scale_factor = mini_height;
    mini_map->small_factor = return_smallest(mini_height, mini_width);
    mini_map->big_factor = return_biggest(mini_height, mini_width);
}