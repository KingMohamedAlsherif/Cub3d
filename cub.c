/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:09:15 by amagoury          #+#    #+#             */
/*   Updated: 2025/04/11 16:11:22 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	cub;

	if (ac != 2)
	{
		ft_printf(2, "%s\n", "Invalid arguments");
		exit(EXIT_FAILURE);
	}
	init(&cub, av[1]);
	cub.mlx_ptr = mlx_init();
	if (!cub.mlx_ptr)
		exit_failure(&cub, "Error\nFailed to initialize mlx");
	// parsing(&cub, av[1]);
	launch_game(&cub);
	return (0);
}