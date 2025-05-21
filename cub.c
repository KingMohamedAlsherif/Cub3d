/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:09:15 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/21 16:10:35 by amagoury         ###   ########.fr       */
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
	init(&cub, av[1]);
	cub.mlx_ptr = mlx_init();
	if (!cub.mlx_ptr)
		exit_failure(&cub, "Error\nFailed to initialize mlx");
	is_parsing(&parsing, av[1]);
	launch_game(&cub);
	return (0);
}
