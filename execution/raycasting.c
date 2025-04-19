
#include "cub3d.h"

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_cub *cub)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if ((y_m >= cub->map->map_height || x_m >= cub->map->map_width))
		return (0);
	if (cub->map->map_arr[y_m] && x_m <= (int)ft_strlen(cub->map->map_arr[y_m]))
		if (cub->map->map_arr[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h_inter(t_cub *cub, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(cub->player->plyr_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = cub->player->plyr_x + (h_y - cub->player->plyr_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y')
			&& x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, cub))
	{
		h_x += x_step;
		h_y += y_step;
	}
	cub->ray->hor_x = h_x;
	cub->ray->hor_y = h_y;
	return (sqrt(pow(h_x - cub->player->plyr_x, 2) + pow(h_y
				- cub->player->plyr_y, 2)));
}

float	get_v_inter(t_cub *cub, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(cub->player->plyr_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = cub->player->plyr_y + (v_x - cub->player->plyr_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x')
			&& y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, cub))
	{
		v_x += x_step;
		v_y += y_step;
	}
	cub->ray->ver_x = v_x;
	cub->ray->ver_y = v_y;
	return (sqrt(pow(v_x - cub->player->plyr_x, 2) + pow(v_y
				- cub->player->plyr_y, 2)));
}

void	cast_rays(t_cub *cub)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	cub->ray->ray_angle = cub->player->plyr_angle - (cub->player->fov_rd / 2);
	while (ray < S_WIDTH)
	{
		cub->ray->wall_flag = 0;
		h_inter = get_h_inter(cub, nor_angle(cub->ray->ray_angle));
		v_inter = get_v_inter(cub, nor_angle(cub->ray->ray_angle));
		if (v_inter <= h_inter)
			cub->ray->distance = v_inter;
		else
		{
			cub->ray->distance = h_inter;
			cub->ray->wall_flag = 1;
		}
		render_wall(cub, ray);
		ray++;
		cub->ray->ray_angle += (cub->player->fov_rd / S_WIDTH);
	}
}
