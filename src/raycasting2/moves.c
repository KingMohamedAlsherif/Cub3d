/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:41:50 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/09 18:51:01 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    normalize_angle(double *angle)
{
    *angle = remainder(*angle, TWO_PI);
    if (*angle < 0)
        *angle += TWO_PI;
}

void    move_player(t_player    *player, int    flag)
{
    double    move_step;
    t_point    new_pos;
    
    player->r_angle += player->turn_dir * player->turn_speed;
    move_step = player->walk_dir * player->walk_speed;
    if (flag == 0)
    {
        new_pos.x = player->pos.x + (cos(player->r_angle) * move_step);
        new_pos.y = player->pos.y + (sin(player->r_angle) * move_step);
    }
    else
    {
        new_pos.x = player->pos.x + (cos(player->r_angle - (M_PI_2)) * move_step);
        new_pos.y = player->pos.y + (sin(player->r_angle - (M_PI_2)) * move_step);
    }
    if (!maphaswallat(new_pos.x, new_pos.y, player))
    {
        player->pos.x = new_pos.x;
        player->pos.y = new_pos.y;
    }
}