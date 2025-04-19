/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:46:11 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/13 16:13:17 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_release(t_mlx_key_data keydata, t_cub *game)
{
	if (keydata.key == MLX_KEY_D)
		game->player->r_l = 0;
	else if (keydata.key == MLX_KEY_A)
		game->player->r_l = 0;
	else if (keydata.key == MLX_KEY_S)
		game->player->u_d = 0;
	else if (keydata.key == MLX_KEY_W)
		game->player->u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT)
		game->player->rot_flag = -0;
	else if (keydata.key == MLX_KEY_RIGHT)
		game->player->rot_flag = 0;
	return (0);
}

int	handle_key(t_mlx_key_data keydata, void *context)
{
	t_cub	*game;

	game = context;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit_success(game);
	else if (keydata.key == MLX_KEY_A)
		game->player->r_l -= 1;
	else if (keydata.key == MLX_KEY_D)
		game->player->r_l += 1;
	else if (keydata.key == MLX_KEY_S)
		game->player->u_d = -1;
	else if (keydata.key == MLX_KEY_W)
		game->player->u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT)
		game->player->rot_flag = -1;
	else if (keydata.key == MLX_KEY_RIGHT)
		game->player->rot_flag = 1;
	return (0);
}

void	turn_player(t_cub *game, int direction)
{
	if (direction == 1)
	{
		game->player->view_angle += ROTATE_SPEED;
		if (game->player->view_angle > 2 * M_PI)
			game->player->view_angle -= 2 * M_PI;
	}
	else
	{
		game->player->view_angle -= ROTATE_SPEED;
		if (game->player->view_angle < 0)
			game->player->view_angle += 2 * M_PI;
	}
}

int	detect_collision(t_map *map_data, float pos_x, float pos_y)
{
	int	grid_x1;
	int	grid_y1;
	int	grid_x2;
	int	grid_y2;

	grid_x1 = (int)(pos_x - 5) / TILE_SIZE;
	grid_y1 = (int)(pos_y - 5) / TILE_SIZE;
	grid_x2 = (int)(pos_x + 5) / TILE_SIZE;
	grid_y2 = (int)(pos_y + 5) / TILE_SIZE;
	if (grid_x1 < 0 || grid_x1 >= map_data->map_width || grid_y1 < 0
		|| grid_y1 >= map_data->map_height || grid_x2 < 0 || grid_x2 >= map_data->map_width
		|| grid_y2 < 0 || grid_y2 >= map_data->map_height)
		return (1);
	return (map_data->map_arr[grid_y1][grid_x1] == '1'
		|| map_data->map_arr[grid_y1][grid_x2] == '1'
		|| map_data->map_arr[grid_y2][grid_x1] == '1'
		|| map_data->map_arr[grid_y2][grid_x2] == '1');
}

void	shift_player(t_cub *game, double delta_x, double delta_y)
{
	int	next_x;
	int	next_y;

	next_x = roundf(game->player->pos_x + delta_x);
	next_y = roundf(game->player->pos_y + delta_y);
	if (!detect_collision(game->map, next_x, next_y))
	{
		game->player->pos_x = next_x;
		game->player->pos_y = next_y;
	}
	else
		exit_failure(game, "Error: Collision detected, player movement blocked.\n");
}