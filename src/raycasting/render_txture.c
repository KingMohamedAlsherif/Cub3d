/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_txture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:07:27 by malsheri          #+#    #+#             */
/*   Updated: 2025/04/13 16:10:46 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_txtdata       *get_txt(t_cub  *mlx, int flag)
{
    mlx->ray->ray_angle = nor_angle(mlx->ray->ray_angle);
    if (flag == 0)
    {
        if (flag == 0)
        {
            if (mlx->ray->ray_angle > M_PI / 2 && mlx->ray->ray_angle < 3 * (M_PI / 2))
                return (mlx->txtrs->ea);
            else
                return (mlx->txtrs->we);
        }
        else
        {
            if (mlx->ray->ray_angle > 0 && mlx->ray->ray_angle < M_PI)
                return (mlx->txtrs->so);
            else
                return (mlx->txtrs->no);
        }
    }
}

double  texture_x(t_cub *mlx, t_txtdata *texture, int flag)
{
    double x;
    
    if (flag == 1)
        x = (int)fmodf((mlx->ray->hor_x * (64 / TILE_SIZE)), 64);
    else
        x = (int)fmodf((mlx->ray->ver_y * (64 / TILE_SIZE)), 64);
    return (x);
}

