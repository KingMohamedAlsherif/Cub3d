/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:11:11 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/11 17:33:57 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    set_horz_ray_point(double ray_angle, t_ray *ray, t_player   *player)
{
    ray->found_h_hit = false;
    init_point(&ray->horz_wall_hit, 0, 0);
    ray->horz_wall_content = 0;
    ray->h_intercept = floor(player->pos.y / TILE_SIZE) * TILE_SIZE;
    if (ray->is_ray_facing_down)
        ray->h_intercept += TILE_SIZE;
    ray->h_intercept.x += player->pos.x + ((ray->h_intercept.y - player->pos.y) / tan(ray->ray_angle));
    ray->h_step.y = TILE_SIZE;
    if (ray->is_ray_facing_up)
        ray->h_step.y *= -1;
    ray->h_step.x = TILE_SIZE / tan(ray->ray_angle);
    if (ray->is_ray_facing_left && ray->h_step.x > 0)
        ray->h_step.x *= -1;
    if (ray->is_ray_facing_right && ray->h_step.x < 0)
        ray->h_step.x *= -1;
    ray->next_h_touch.x = ray->h_intercept.x;
    ray->next_h_touch.y = ray->h_intercept.y;
}

void    cast_horz_ray(double ray_angle, t_ray *ray, t_player *player)
{
    set_h_ray_point(ray_angle, ray, player);
    while (is_inside_map(ray->next_h_touch.x, ray->next_h_touch.y, player))
    {
        if (ray->is_ray_facing_up)
            init_point(&ray->to_check, ray->next_h_touch.x,ray->next_h_touch.y - 1);
        else
            init_point(&ray->to_check, ray->next_h_touch.x, ray->next_h_touch.y);
        if (maphaswallat(ray->to_check.x, ray->to_check.y, player))
        {
            ray->horz_wallhit.x = ray->next_h_touch.x;
            ray->horz_wallhit.y = ray->next_h_touch.y;
            ray->horz_wall_content = get_map_at(floor(ray->to_check.y / TILE_SIZE),
                                                floor(ray->to_check.x / TILE_SIZE), player);
            ray->found_h_hit = true;
            break ;
        }
        else
        {
            ray->next_h_touch.x += ray->h_step.x;
            ray->next_h_touch.y += ray->h_step.y;
        }  
    }
}

