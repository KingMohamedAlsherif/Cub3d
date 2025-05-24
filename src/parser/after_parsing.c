/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 21:44:03 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/24 14:03:25 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "parse.h"

static void validate_conversion(t_game *cub);

// Convert parsing data to cub3d structure
void convert_parsing_to_cub3d(t_game *cub, t_cub *parsing)
{
	cub->map->map_arr = parsing->map;
	cub->txtrs->f_color = parsing->colors.floor_color;
	cub->map->map_width = parsing->width;
	cub->map->map_height = parsing->height;
	cub->txtrs->c_color = parsing->colors.ceiling_color;
	cub->txtrs->f_arr[0] = parsing->colors.floor_red;
	cub->txtrs->f_arr[1] = parsing->colors.floor_green;
	cub->txtrs->f_arr[2] = parsing->colors.floor_blue;
	cub->txtrs->c_arr[0] = parsing->colors.ceiling_red;
	cub->txtrs->c_arr[1] = parsing->colors.ceiling_green;
	cub->txtrs->c_arr[2] = parsing->colors.ceiling_blue;
	convert_textures(cub, parsing);
	validate_conversion(cub);
}

static void	validate_img(t_game *cub, char *img_path, t_txtdata *txtr)
{
	int	width;
	int	height;

	txtr->img = mlx_xpm_file_to_image(cub->mlx_ptr, img_path,
			&width, &height);
	if (!txtr->img)
		exit_failure(cub, "Invalid texture path");
	txtr->height = height;
	txtr->width = width;
	txtr->addr = mlx_get_map_addr(txtr->img,
				&txtr->bpp, &txtr->line_len, &txtr->endian);
	if (!txtr->addr)
	{
		mlx_destroy_image(cub->mlx_ptr, txtr->img);
		exit_failure(cub, "Failed to get texture address");
	}
	
}

void	convert_textures(t_game *cub, t_cub *parsing)
{
	if (parsing->textures.north)
		validate_img(cub, parsing->textures.north, cub->txtrs->no);
	if (parsing->textures.south)
		validate_img(cub, parsing->textures.south, cub->txtrs->so);
	if (parsing->textures.west)
		validate_img(cub, parsing->textures.west, cub->txtrs->we);
	if (parsing->textures.east)
		validate_img(cub, parsing->textures.east, cub->txtrs->ea);
}

static void	validate_conversion(t_game *cub)
{
    if (!cub->map || !cub->map->map_arr)
    {
        write(2, "Error: Map data is missing.\n", 28);
        exit(EXIT_FAILURE);
    }
    if (cub->player->plyr_x < 0 || cub->player->plyr_y < 0)
    {
        write(2, "Error: Player position is invalid.\n", 35);
        exit(EXIT_FAILURE);
    }
    if (!cub->txtrs || !cub->txtrs->no || !cub->txtrs->so || 
        !cub->txtrs->we || !cub->txtrs->ea)
    {
        write(2, "Error: Missing textures.\n", 25);
        exit(EXIT_FAILURE);
    }
    if (!cub->txtrs->no->addr || !cub->txtrs->so->addr || 
        !cub->txtrs->we->addr || !cub->txtrs->ea->addr)
    {
        write(2, "Error: Texture data is invalid.\n", 32);
        exit(EXIT_FAILURE);
    }
    if (cub->txtrs->f_color < 0 || cub->txtrs->c_color < 0)
    {
        write(2, "Error: Floor or ceiling color is invalid.\n", 42);
        exit(EXIT_FAILURE);
    }
}