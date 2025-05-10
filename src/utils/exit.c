
#include "../cub3d.h"

static void	exit_mlx(t_game *cub)
{
	if (cub->txtrs)
	{
		if (cub->txtrs->no->img)
			mlx_destroy_image(cub->mlx_ptr, cub->txtrs->no->img);
		if (cub->txtrs->so->img)
			mlx_destroy_image(cub->mlx_ptr, cub->txtrs->so->img);
		if (cub->txtrs->we->img)
			mlx_destroy_image(cub->mlx_ptr, cub->txtrs->we->img);
		if (cub->txtrs->ea->img)
			mlx_destroy_image(cub->mlx_ptr, cub->txtrs->ea->img);
		ft_free(&cub->txtrs->no, 'p');
		ft_free(&cub->txtrs->so, 'p');
		ft_free(&cub->txtrs->we, 'p');
		ft_free(&cub->txtrs->ea, 'p');
		ft_free(&cub->txtrs, 'p');
	}
	if (cub->img->img)
		mlx_destroy_image(cub->mlx_ptr, cub->img->img);
	ft_free(&cub->img, 'p');
	if (cub->win_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->mlx_ptr)
		free(cub->mlx_ptr);
}

static void	exit_clean(t_game *cub)
{
	ft_free(&cub->file.file_arr, 'a');
	ft_free(&cub->map->map_arr, 'a');
	ft_free(&cub->map, 'p');
	ft_free(&cub->player, 'p');
	ft_free(&cub->ray, 'p');
	exit_mlx(cub);
}

void	exit_failure(t_game *cub, char *err_msg)
{
	exit_clean(cub);
	if (*err_msg)
		ft_printf(2, "%s\n", err_msg);
	exit(EXIT_FAILURE);
}

int	exit_success(t_game *cub)
{
	exit_clean(cub);
	exit(EXIT_SUCCESS);
	return (0);
}
