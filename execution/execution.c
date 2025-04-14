
#include "cub3d.h"

void	start_the_game(t_cub *cub)
{
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, S_WIDTH, S_HEIGHT, "cub3d");
	if (!cub->win_ptr)
		exit_failure(cub, MLX_ERR);
	mlx_hook(cub->win_ptr, MLX_PRESS, MLX_RELEASE, &mlx_key, cub);
	mlx_hook(cub->win_ptr, MLX_RELEASE, MLX_RELEASE, &key_reles, cub);
	mlx_hook(cub->win_ptr, ON_DESTROY, 0, exit_success, cub);
	mlx_loop_hook(cub->mlx_ptr, &game_loop, cub);
	mlx_loop(cub->mlx_ptr);
	exit_success(cub);
}

int	game_loop(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (cub->img->img)
		mlx_destroy_image(cub->mlx_ptr, cub->img->img);
	cub->img->img = mlx_new_image(cub->mlx_ptr, S_WIDTH, S_HEIGHT);
	cub->img->addr = mlx_get_map_addr(cub->img->img, &cub->img->bpp,
			&cub->img->line_len, &cub->img->endian);
	hook(cub, 0, 0);
	cast_rays(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img->img, 0, 0);
	return (0);
}

void	hook(t_cub *cub, double move_x, double move_y)
{
	if (cub->player->rot_flag == 1)
		rotate_player(cub, 1);
	if (cub->player->rot_flag == -1)
		rotate_player(cub, 0);
	if (cub->player->r_l == 1)
	{
		move_x = -sin(cub->player->plyr_angle) * PLAYER_SPEED;
		move_y = cos(cub->player->plyr_angle) * PLAYER_SPEED;
	}
	if (cub->player->r_l == -1)
	{
		move_x = sin(cub->player->plyr_angle) * PLAYER_SPEED;
		move_y = -cos(cub->player->plyr_angle) * PLAYER_SPEED;
	}
	if (cub->player->u_d == 1)
	{
		move_x = cos(cub->player->plyr_angle) * PLAYER_SPEED;
		move_y = sin(cub->player->plyr_angle) * PLAYER_SPEED;
	}
	if (cub->player->u_d == -1)
	{
		move_x = -cos(cub->player->plyr_angle) * PLAYER_SPEED;
		move_y = -sin(cub->player->plyr_angle) * PLAYER_SPEED;
	}
	move_player(cub, move_x, move_y);
}
