
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

/*
	*	void	init(t_game *cub, char *input_file)
	{
		-	cub->mlx = NULL;
			used to store the mlx pointer into that variable, we init it to NULL.
		-	cub->win = NULL;
			used to store the window pointer into that variable,
			we init it to NULL.
		-	init_file(&cub->file, input_file);
			used to init the file struct.
		-	init_player(&cub->player);
			used to init the player struct.
	}
	
	*	static void	init_file(t_file *file, char *input_file)
	{
		-	file->file_arr = NULL;
			used to store the whole file into that array.
		-	file->filepath_len = (int)ft_strlen(input_file);
			used to store the length of the input file path (the given map).
		-	file->file_len = 0;
			used to store the length of the file, (the given elements & map).
		-	file->stage = 1;
			used to store the stage of the parsing process.
			- 1 for the elements.
			- 2 for the map.
			- we use it to validate if the map follows the right order.
	}

	*	static void	init_map(t_map *map)
	{
		-	map->map_arr = NULL;
			used to store the map into that array.
		-	map->map_width = 0;
			used to store the width of the map.
		-	map->map_height = 0;
			used to store the height of the map.
		-	map->map_st = 0;
			used to store the starting index of the map.
		-	map->map_end = 0;
			used to store the ending index of the map.
		-	map->wall_counter = 0;
			used to store the number of walls in the map.
		-	map->plyr_counter = 0;
			used to store the number of players in the map.
		-	map->plyr_direction = '\0';
			used to store the position of the player in the map.
	}

	*	static void	init_player(t_player *player)
	{
		-	player->plyr_x = -1;
			used to store the x position of the player->
		-	player->plyr_y = -1;
			used to store the y position of the player->
		-	player->angle = -1;
			used to store the angle of the player->
		-	player->fov_rd = -1;
			used to store the field of view of the player->
		-	player->rot = -1;
			used to store the rotation of the player->
		-	player->l_r = -1;
			used to store the left right movement of the player->
		-	player->u_d = -1;
			used to store the up down movement of the player->
	}
*/
