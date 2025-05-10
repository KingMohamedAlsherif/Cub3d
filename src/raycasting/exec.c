/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:39:37 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/13 15:43:29 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	launch_game(t_game *cub)
{
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, S_WIDTH, S_HEIGHT, "cub3d");
	if (!cub->win_ptr)
		exit_failure(cub, "Error: Failed to create a new window.\n");
	mlx_hook(cub->win_ptr, MLX_PRESS, MLX_RELEASE, &mlx_key, cub);
	mlx_hook(cub->win_ptr, MLX_RELEASE, MLX_RELEASE, &key_release, cub);
	mlx_hook(cub->win_ptr, ON_DESTROY, 0, exit_success, cub);
	mlx_loop_hook(cub->mlx_ptr, &render_loop, cub);
	mlx_loop(cub->mlx_ptr);
	exit_success(cub);
}

int	render_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->img->img)
		mlx_destroy_image(game->mlx_ptr, game->img->img);
	game->img->img = mlx_new_image(game->mlx_ptr, S_WIDTH, S_HEIGHT);
	game->img->addr = mlx_get_map_addr(game->img->img, &game->img->bpp,
			&game->img->line_len, &game->img->endian);
	update_player(game, 0, 0);
	project_rays(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->img, 0, 0);
	return (0);
}

void	update_player(t_game *game, double delta_x, double delta_y)
{
	if (game->player->rot_flag == 1)
		turn_player(game, 1);
	if (game->player->rot_flag == -1)
		turn_player(game, 0);
	if (game->player->r_l == 1)
	{
		delta_x = -sin(game->player->plyr_angle) * PLAYER_SPEED;
		delta_y = cos(game->player->plyr_angle) * PLAYER_SPEED;
	}
	if (game->player->r_l == -1)
	{
		delta_x = sin(game->player->plyr_angle) * PLAYER_SPEED;
		delta_y = -cos(game->player->plyr_angle) * PLAYER_SPEED;
	}
	if (game->player->u_d == 1)
	{
		delta_x = cos(game->player->plyr_angle) * PLAYER_SPEED;
		delta_y = sin(game->player->plyr_angle) * PLAYER_SPEED;
	}
	if (game->player->u_d == -1)
	{
		delta_x = -cos(game->player->plyr_angle) * PLAYER_SPEED;
		delta_y = -sin(game->player->plyr_angle) * PLAYER_SPEED;
	}
	shift_player(game, delta_x, delta_y);
}