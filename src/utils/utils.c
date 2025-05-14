
#include "../cub3d.h"

void	use_atoi(t_game *cub, char *str_nbr, int *counter)
{
	t_atoi	res;
	int		nbr;

	if (!str_nbr || !*str_nbr)
		return (exit_failure(cub, "COLOR_ERR"));
	res = ft_atoi(str_nbr);
	if (res.error)
		return (exit_failure(cub, "COLOR_ERR"));
	nbr = (int)res.nbr;
	if (nbr < 0 || nbr > 255)
		return (exit_failure(cub, "COLOR_ERR"));
	*counter = nbr;
}

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
