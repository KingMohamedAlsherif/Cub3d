/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:09:15 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/24 16:24:03 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	cub;
	t_cub	parsing;
	if (ac != 2)
	{
		write(2, "Error\nInvalid number of arguments\n", 35);
		exit(EXIT_FAILURE);
	}
	ft_bzero(&parsing, sizeof(t_cub));
	// cub = (t_game){0};
	init(&cub, av[1]);
	cub.mlx_ptr = mlx_init();
	if (!cub.mlx_ptr)
	{
		write(2, "Error\nmlx_ptr is NULL before mlx_new_window\n", 44);
		exit(EXIT_FAILURE);
	}
	printf("mlx_ptr: %p\n", cub.mlx_ptr);
	is_parsing(&parsing, av[1], &cub);
	convert_parsing_to_cub3d(&cub, &parsing);
	launch_game(&cub);
	return (0);
}