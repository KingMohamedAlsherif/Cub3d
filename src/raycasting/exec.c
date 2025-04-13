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

#include "cub3d.h"

void    init_txtures(t_cub  *cub)
{
    t_txtrs *txtrs;
    t_texture texture;

    texture = cub->texture;
    txtrs = (t_txtrs *)ft_calloc(1, sizeof(t_txtrs));
    cub->txtrs = txtrs;
    txtrs->no = (t_txtdata *)ft_calloc(1, sizeof(t_txtdata));
    txtrs->so = (t_txtdata *)ft_calloc(1, sizeof(t_txtdata));
    txtrs->we = (t_txtdata *)ft_calloc(1, sizeof(t_txtdata));
    txtrs->ea = (t_txtdata *)ft_calloc(1, sizeof(t_txtdata));
    txtrs->no->img = texture.no_img;
    txtrs->so->img = texture.so_img;
    txtrs->we->img = texture.we_img;
    txtrs->ea->img = texture.ea_img;
    txtrs->no->addr = mlx_get_map_addr(txtrs->no->img, &txtrs->no->bpp, &txtrs->no->line_len, &txtrs->no->endian);
    txtrs->so->addr = mlx_get_map_addr(txtrs->so->img, &txtrs->so->bpp, &txtrs->so->line_len, &txtrs->so->endian);
    txtrs->we->addr = mlx_get_map_addr(txtrs->we->img, &txtrs->we->bpp, &txtrs->we->line_len, &txtrs->we->endian);
    txtrs->ea->addr = mlx_get_map_addr(txtrs->ea->img, &txtrs->ea->bpp, &txtrs->ea->line_len, &txtrs->ea->endian);
}