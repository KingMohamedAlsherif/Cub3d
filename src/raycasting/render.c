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

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_wall(t_cub *cub, int t_pix, int b_pix, double wall_h)
{
	int			color;
	t_txtdata	*txt;
	double		x_o;
	double		y_o;
	double		fact;

	txt = get_txt(cub, cub->ray->wall_flag);
	fact = (double)txt->height / wall_h;
	x_o = texture_x(cub, txt, cub->ray->wall_flag);
	y_o = (t_pix - (S_HEIGHT / 2) + (wall_h / 2)) * fact;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		color = *(unsigned int *)(txt->addr + ((int)y_o * txt->line_len
					+ (int)x_o * (txt->bpp / 8)));
		my_mlx_pixel_put(cub, cub->ray->indx, t_pix++, color);
		y_o += fact;
	}
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void	render_wall(t_cub *cub, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	cub->ray->distance *= cos(nor_angle(cub->ray->ray_angle
				- cub->player->plyr_angle));
	wall_h = (TILE_SIZE / cub->ray->distance) * ((S_WIDTH / 2)
			/ tan(cub->player->fov_rd / 2));
	b_pix = (S_HEIGHT / 2) + (wall_h / 2);
	t_pix = (S_HEIGHT / 2) - (wall_h / 2);
	if (b_pix > S_HEIGHT)
		b_pix = S_HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	cub->ray->indx = ray;
	draw_wall(cub, t_pix, b_pix, wall_h);
	draw_floor_ceiling(cub, ray, t_pix, b_pix);
}