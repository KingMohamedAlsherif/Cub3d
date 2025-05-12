#include "../cub3d.h"
// Create a function that convert some variables in parsing header to variables in the cub3d header

void    convert_parsing_to_cub3d(t_game *cub, t_cub *parsing)
{
    cub->map->map_arr = parsing->map;
    // cub->txtrs = parsing->txtrs;
    // cub->texture = parsing->texture;
    cub->mlx_ptr = parsing->mlx;
    cub->win_ptr = parsing->win;
    cub->map->map_width = parsing->width;
    cub->map->map_height = parsing->height;
    cub->player->plyr_x = parsing->player_x;
    cub->player->plyr_y = parsing->player_y;
    cub->map->plyr_direction = parsing->player_dir; // Assuming player_direction exists in parsing
    convert_textures(cub, parsing);
}


static void	validate_img(t_game *cub, char *img_path, t_txtdata *txtr)
{
    int	width;
    int	height;

    if (txtr->img)
        return;

    // if (!ft_strrchr(img_path, '.xpm'))
    //     return;
    txtr->img = mlx_xpm_file_to_image(cub->mlx_ptr, img_path, &width, &height);
    if (!txtr->img)
        return;
    txtr->height = height;
    txtr->width = width;
    txtr->addr = mlx_get_data_addr(txtr->img,
            &txtr->bpp, &txtr->line_len, &txtr->endian);
}

void    convert_textures(t_game *cub, t_cub *parsing)
{
    t_txtrs     *txtrs;

    txtrs = cub->txtrs;
    if (parsing->textures.north)
        validate_img(cub, parsing->textures.north, txtrs->no);
    if (parsing->textures.south)
        validate_img(cub, parsing->textures.south, txtrs->so);
    if (parsing->textures.west)
        validate_img(cub, parsing->textures.west, txtrs->we);
    if (parsing->textures.east)
        validate_img(cub, parsing->textures.east, txtrs->ea);
}