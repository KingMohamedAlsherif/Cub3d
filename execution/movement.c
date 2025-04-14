
#include "cub3d.h"

int	key_reles(t_mlx_key_data keydata, t_cub *cub)
{
	if (keydata.key == MLX_KEY_D)
		cub->player->r_l = 0;
	else if (keydata.key == MLX_KEY_A)
		cub->player->r_l = 0;
	else if (keydata.key == MLX_KEY_S)
		cub->player->u_d = 0;
	else if (keydata.key == MLX_KEY_W)
		cub->player->u_d = 0;
	else if (keydata.key == MLX_KEY_LEFT)
		cub->player->rot_flag = 0;
	else if (keydata.key == MLX_KEY_RIGHT)
		cub->player->rot_flag = 0;
	return (0);
}

int	mlx_key(t_mlx_key_data keydata, void *ml)
{
	t_cub	*cub;

	cub = ml;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit_success(cub);
	else if (keydata.key == MLX_KEY_A)
		cub->player->r_l -= 1;
	else if (keydata.key == MLX_KEY_D)
		cub->player->r_l += 1;
	else if (keydata.key == MLX_KEY_S)
		cub->player->u_d = -1;
	else if (keydata.key == MLX_KEY_W)
		cub->player->u_d = 1;
	else if (keydata.key == MLX_KEY_LEFT)
		cub->player->rot_flag = -1;
	else if (keydata.key == MLX_KEY_RIGHT)
		cub->player->rot_flag = 1;
	return (0);
}

void	rotate_player(t_cub *cub, int i)
{
	if (i == 1)
	{
		cub->player->plyr_angle += ROTATE_SPEED;
		if (cub->player->plyr_angle > 2 * M_PI)
			cub->player->plyr_angle -= 2 * M_PI;
	}
	else
	{
		cub->player->plyr_angle -= ROTATE_SPEED;
		if (cub->player->plyr_angle < 0)
			cub->player->plyr_angle += 2 * M_PI;
	}
}

int	check_collision(t_map *data, float new_x, float new_y)
{
	int	map_x1;
	int	map_y1;
	int	map_x2;
	int	map_y2;

	map_x1 = (int)(new_x - 5) / TILE_SIZE;
	map_y1 = (int)(new_y - 5) / TILE_SIZE;
	map_x2 = (int)(new_x + 5) / TILE_SIZE;
	map_y2 = (int)(new_y + 5) / TILE_SIZE;
	if (map_x1 < 0 || map_x1 >= data->map_width || map_y1 < 0
		|| map_y1 >= data->map_height || map_x2 < 0 || map_x2 >= data->map_width
		|| map_y2 < 0 || map_y2 >= data->map_height)
		return (1);
	return (data->map_arr[map_y1][map_x1] == '1'
		|| data->map_arr[map_y1][map_x2] == '1'
		|| data->map_arr[map_y2][map_x1] == '1'
		|| data->map_arr[map_y2][map_x2] == '1');
}

void	move_player(t_cub *cub, double move_x, double move_y)
{
	int	new_x;
	int	new_y;

	new_x = roundf(cub->player->plyr_x + move_x);
	new_y = roundf(cub->player->plyr_y + move_y);
	if (!check_collision(cub->map, new_x, new_y))
	{
		cub->player->plyr_x = new_x;
		cub->player->plyr_y = new_y;
	}
}
