/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:09:35 by malsheri          #+#    #+#             */
/*   Updated: 2025/05/25 20:12:05 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_malloc(t_game *cub)
{
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->map = (t_map *)ft_calloc(1, sizeof(t_map));
	cub->player = (t_player *)ft_calloc(1, sizeof(t_player));
	cub->img = (t_img *)ft_calloc(1, sizeof(t_img));
	cub->ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	cub->txtrs = (t_txtrs *)ft_calloc(1, sizeof(t_txtrs));
	if (!cub->map || !cub->player || !cub->img || !cub->ray || !cub->txtrs)
		exit_failure(cub, "MALLOC_ERR");
	cub->txtrs->no = (t_txtdata *)ft_calloc(1, sizeof(t_txtdata));
	cub->txtrs->so = (t_txtdata *)ft_calloc(1, sizeof(t_txtdata));
	cub->txtrs->we = (t_txtdata *)ft_calloc(1, sizeof(t_txtdata));
	cub->txtrs->ea = (t_txtdata *)ft_calloc(1, sizeof(t_txtdata));
	if (!cub->txtrs->no || !cub->txtrs->so
		|| !cub->txtrs->we || !cub->txtrs->ea)
		exit_failure(cub, "MALLOC_ERR");
	cub->txtrs->f_color = -1;
	cub->txtrs->c_color = -1;
}

void	init_structs(t_game *cub, t_file *file, char *input_file)
{
	t_map		*map;
	t_player	*player;

	map = cub->map;
	player = cub->player;
	file->file_arr = NULL;
	file->filepath_len = (int)ft_strlen(input_file);
	file->file_len = 0;
	file->stage = 1;
	map->map_arr = NULL;
	map->map_width = 0;
	map->map_height = 0;
	map->map_st = 0;
	map->map_end = 0;
	map->wall_counter = 0;
	map->plyr_counter = 0;
	map->plyr_direction = '\0';
	player->plyr_x = -1;
	player->plyr_y = -1;
	player->plyr_angle = -1;
	player->fov_rd = FOV * (M_PI / 180);
	player->r_l = 0;
	player->u_d = 0;
	player->rot_flag = 0;
}

void	init_txtr(t_txtdata *txtr)
{
	txtr->img = NULL;
	txtr->addr = NULL;
	txtr->bpp = 0;
	txtr->line_len = 0;
	txtr->endian = 0;
	txtr->width = 0;
	txtr->height = 0;
}

void	init(t_game *cub, char *input_file)
{
	init_malloc(cub);
	init_structs(cub, &cub->file, input_file);
	init_txtr(cub->txtrs->no);
	init_txtr(cub->txtrs->so);
	init_txtr(cub->txtrs->we);
	init_txtr(cub->txtrs->ea);
}
