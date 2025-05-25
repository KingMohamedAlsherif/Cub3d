/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:09:45 by malsheri          #+#    #+#             */
/*   Updated: 2025/05/25 20:12:14 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_angle(t_game *cub, char direction, int x, int y)
{
	if (direction == 'N')
		cub->player->plyr_angle = 3 * M_PI / 2;
	else if (direction == 'S')
		cub->player->plyr_angle = M_PI / 2;
	else if (direction == 'E')
		cub->player->plyr_angle = 0;
	else if (direction == 'W')
		cub->player->plyr_angle = M_PI;
	cub->player->plyr_x = x * TILE_SIZE + TILE_SIZE / 2;
	cub->player->plyr_y = y * TILE_SIZE + TILE_SIZE / 2;
}

int	create_rgb(int *color_arr)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = color_arr[0];
	g = color_arr[1];
	b = color_arr[2];
	a = 0x00000000;
	return (r << 16 | g << 8 | b | a);
}
