
#include "cub3d.h"

t_txtdata	*get_txt(t_cub *cub, int flag)
{
	cub->ray->ray_angle = nor_angle(cub->ray->ray_angle);
	if (flag == 0)
	{
		if (cub->ray->ray_angle > M_PI / 2 && cub->ray->ray_angle < 3 * (M_PI
				/ 2))
			return (cub->txtrs->we);
		else
			return (cub->txtrs->ea);
	}
	else
	{
		if (cub->ray->ray_angle > 0 && cub->ray->ray_angle < M_PI)
			return (cub->txtrs->so);
		else
			return (cub->txtrs->no);
	}
}

double	texture_x(t_cub *cub, t_txtdata *texture, int flag)
{
	double	x_o;

	(void)texture;
	if (flag == 1)
		x_o = ((float)((int)cub->ray->hor_x % TILE_SIZE) / TILE_SIZE)
			* texture->width;
	else
		x_o = ((float)((int)cub->ray->ver_y % TILE_SIZE) / TILE_SIZE)
			* texture->width;
	return (x_o);
}

void	draw_floor_ceiling(t_cub *cub, int ray, int t_pix, int b_pix)
{
	int	i;
	int	color;

	i = b_pix;
	color = cub->txtrs->f_color;
	while (i < S_HEIGHT)
		my_mlx_pixel_put(cub, ray, i++, color);
	i = 0;
	color = cub->txtrs->c_color;
	while (i < t_pix)
		my_mlx_pixel_put(cub, ray, i++, color);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}
