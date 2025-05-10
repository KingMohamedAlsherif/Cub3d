/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:05:04 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/13 17:11:18 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



t_map *init_argument()
{
    t_map *map;

    map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->map_arr = init_map();
    map->map_width = 25;
    map->map_height = 9;
    map->p_x = 12;
    map->p_y = 2;
    return (map);
}



void    init_player_data(t_game  cub)
{
    char c;

    c = cub.map->map_arr[cub.map->p_y][cub.map->p_x];
    if (c == 'N')
        cub.player->plyr_angle = 3 * M_PI / 2;
    else if (c == 'S')
        cub.player->plyr_angle = M_PI / 2;
    else if (c == 'W')
        cub.player->plyr_angle = M_PI;
    else if (c == 'E')
        cub.player->plyr_angle = 0;
    else
        cub.player->plyr_angle = M_PI; // default angle for testing need to removed after adding parsing
    cub.player->plyr_x = cub.map->p_x * TILE_SIZE + TILE_SIZE / 2;
    cub.player->plyr_y = cub.map->p_y * TILE_SIZE + TILE_SIZE / 2;
    cub.player->fov_rd = (FOV * M_PI) / 180;
}