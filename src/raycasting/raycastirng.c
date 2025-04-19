/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastirng.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:21:15 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/13 16:55:50 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_intersection(float angle, float *point, float *increment, int is_horizontal)
{
	if (is_horizontal)
	{
		if (angle > 0 && angle < M_PI)
		{
			*point += TILE_SIZE;
			return (-1);
		}
		*increment *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*point += TILE_SIZE;
			return (-1);
		}
		*increment *= -1;
	}
	return (1);
}

int	obstacle_hit(float x, float y, t_cub *game)
{
	int	grid_x;
	int	grid_y;

	if (x < 0 || y < 0)
		return (0);
	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	if ((grid_y >= game->map->map_height || grid_x >= game->map->map_width))
		return (0);
	if (game->map->map_arr[grid_y] && grid_x <= (int)ft_strlen(game->map->map_arr[grid_y]))
		if (game->map->map_arr[grid_y][grid_x] == '1')
			return (0);
	return (1);
}

float	calc_h_intersection(t_cub *game, float angle)
{
	float	hor_x;
	float	hor_y;
	float	delta_x;
	float	delta_y;
	int		offset;

	delta_y = TILE_SIZE;
	delta_x = TILE_SIZE / tan(angle);
	hor_y = floor(game->player->plyr_y / TILE_SIZE) * TILE_SIZE;
	offset = check_intersection(angle, &hor_y, &delta_y, 1);
	hor_x = game->player->plyr_x + (hor_y - game->player->plyr_y) / tan(angle);
	if ((unit_circle(angle, 'y') && delta_x > 0) || (!unit_circle(angle, 'y')
			&& delta_x < 0))
		delta_x *= -1;
	while (obstacle_hit(hor_x, hor_y - offset, game))
	{
		hor_x += delta_x;
		hor_y += delta_y;
	}
	game->ray->hor_x = hor_x;
	game->ray->hor_y = hor_y;
	return (sqrt(pow(hor_x - game->player->plyr_x, 2) + pow(hor_y
				- game->player->plyr_y, 2)));
}

float	calc_v_intersection(t_cub *game, float angle)
{
	float	vert_x;
	float	vert_y;
	float	delta_x;
	float	delta_y;
	int		offset;

	delta_x = TILE_SIZE;
	delta_y = TILE_SIZE * tan(angle);
	vert_x = floor(game->player->plyr_x / TILE_SIZE) * TILE_SIZE;
	offset = check_intersection(angle, &vert_x, &delta_x, 0);
	vert_y = game->player->plyr_y + (vert_x - game->player->plyr_x) * tan(angle);
	if ((unit_circle(angle, 'x') && delta_y < 0) || (!unit_circle(angle, 'x')
			&& delta_y > 0))
		delta_y *= -1;
	while (obstacle_hit(vert_x - offset, vert_y, game))
	{
		vert_x += delta_x;
		vert_y += delta_y;
	}
	game->ray->ver_x = vert_x;
	game->ray->ver_y = vert_y;
	return (sqrt(pow(vert_x - game->player->plyr_x, 2) + pow(vert_y
				- game->player->plyr_y, 2)));
}

void	project_rays(t_cub *game)
{
	double	hor_dist;
	double	vert_dist;
	int		ray_idx;

	ray_idx = 0;
	game->ray->ray_angle = game->player->plyr_angle - (game->player->fov_rd / 2);
	while (ray_idx < S_WIDTH)
	{
		game->ray->wall_flag = 0;
		hor_dist = calc_h_intersection(game, nor_angle(game->ray->ray_angle));
		vert_dist = calc_v_intersection(game, nor_angle(game->ray->ray_angle));
		if (vert_dist <= hor_dist)
			game->ray->distance = vert_dist;
		else
		{
			game->ray->distance = hor_dist;
			game->ray->wall_flag = 1;
		}
		render_wall(game, ray_idx);
		ray_idx++;
		game->ray->ray_angle += (game->player->fov_rd / S_WIDTH);
	}
}