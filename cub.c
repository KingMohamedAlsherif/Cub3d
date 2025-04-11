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

int main(int ac, char **av)
{
    t_cub game;

    if (ac != 2)
    {
        (write(2, "No enough args\n", 15), exit(1));
    }
    is_parsing(&game, av[1]);
    printf("Columns: %d, Rows: %d\n", game.cols, game.rows); // Debug print

    game.mlx = mlx_init();
    // if (!game.mlx)
    //     return (1);

    game.window = mlx_new_window(game.mlx,1200, 1200, "cub3D for now");
    // if (!game.window)
    //     return (1);

    mlx_loop(game.mlx);
    return (0);
}