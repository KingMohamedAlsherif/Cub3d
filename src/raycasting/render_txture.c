/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_txture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:07:27 by malsheri          #+#    #+#             */
/*   Updated: 2025/05/25 20:17:42 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_txtdata	*fetch_texture(t_game *game, int is_hori)
{
	game->ray->ray_angle = nor_angle(game->ray->ray_angle);
	if (is_hori == 0)
	{
		if (game->ray->ray_angle > M_PI / 2 && game->ray->ray_angle < 3 * (M_PI
				/ 2))
			return (game->txtrs->we);
		else
			return (game->txtrs->ea);
	}
	else
	{
		if (game->ray->ray_angle > 0 && game->ray->ray_angle < M_PI)
			return (game->txtrs->so);
		else
			return (game->txtrs->no);
	}
}

double	get_texture_coord(t_game *game, t_txtdata *txt, int is_hori)
{
	double	tex_coord;

	(void)txt;
	if (is_hori == 1)
		tex_coord = ((float)((int)game->ray->hor_x % TILE_SIZE) / TILE_SIZE)
			* txt->width;
	else
		tex_coord = ((float)((int)game->ray->ver_y % TILE_SIZE) / TILE_SIZE)
			* txt->width;
	return (tex_coord);
}

void	draw_floor_ceiling(t_game *game, int col, int top_px, int bot_px)
{
	int	idx;
	int	shade;

	idx = bot_px;
	shade = game->txtrs->f_color;
	while (idx < S_HEIGHT)
		my_mlx_pixel_put(game, col, idx++, shade);
	idx = 0;
	shade = game->txtrs->c_color;
	while (idx < top_px)
		my_mlx_pixel_put(game, col, idx++, shade);
}

int	unit_circle(float angle, char axis)
{
	if (axis == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (axis == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}
