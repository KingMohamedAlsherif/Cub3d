/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:02:05 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/09 16:55:04 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"


bool maphaswallat(double x, double y, t_player *player)
{
    int mapx;
    int mapy;

    // mapx = floor(x / TILE_SIZE); // UNCOMPLETED
    // mapy = floor(y / TILE_SIZE); // UNCOMPLETED
    if (x < 0 || x > player->map3d.width * TILE_SIZE || y < 0 || y > player->map3d.height * TILE_SIZE)
        return (true);
    if (player->map3d.map[mapy][mapx] == '0')
        return (false);
    return (true);
}

int get_map_at(int  i, int  j, t_player *player)
{
    return (player->map3d.map[i][j]);
}

bool  is_inside_map(double x, double y, t_player *player)
{
    return (x >= 0 && x <= player->map3d.width * TILE_SIZE && y >= 0 && y <= player->map3d.height * TILE_SIZE);
}

int     return_color(t_cub  *cub, int   tilecolor)
{
    if (cub->keys.t == true)
        return (0x00FFFFFF);
    else
        return (tilecolor);
}

void render_map(t_cub *cub) {
    int i;
    int j;
    t_point tile;
    int tilecolor;
    t_rect rect;

    i = -1;
    while (++i < cub->player.map3d.height) {
        j = -1;
        while (++j < cub->player.map3d.width) {
            init_point(&tile, j * TILE_SIZE, i * TILE_SIZE);
            if (cub->player.map3d.map[i][j] == '1')
                tilecolor = cub->player.map3d.map_wall_color;
            else
                tilecolor = cub->player.map3d.map_bg_color;
            rect = init_rect(tile.x * cub->player.map3d.x_scale_factor,
                    tile.y * cub->player.map3d.y_scale_factor,
                    TILE_SIZE * cub->player.map3d.x_scale_factor,
                    TILE_SIZE * cub->player.map3d.y_scale_factor);
            draw_rectangle(&cub->img, rect, tilecolor);
        }
    }
}