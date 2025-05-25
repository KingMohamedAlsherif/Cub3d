/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:09:15 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/25 20:32:11 by malsheri         ###   ########.fr       */
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
	init(&cub, av[1]);
	ft_bzero(&parsing, sizeof(t_cub));
	is_parsing(&parsing, av[1], &cub);
	cub.mlx_ptr = mlx_init();
	if (!cub.mlx_ptr)
		exit_failure(&cub, "Failed to initialize mlx");
	convert_parsing_to_cub3d(&cub, &parsing);
	launch_game(&cub);
	return (0);
}
