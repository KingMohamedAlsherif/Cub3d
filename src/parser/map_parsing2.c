/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagoury <amagoury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:35:55 by aishamagour       #+#    #+#             */
/*   Updated: 2025/05/21 08:33:32 by amagoury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_invalid_neighbor(char center, char neighbor, char player)
{
	if ((center == '0' || center == player) && neighbor == ' ')
		return (1);
	if (center == ' ' && (neighbor == '0' || neighbor == player))
		return (1);
	return (0);
}

int	check_void(int i, int j, t_cub *game)
{
	char	c;

	c = game->map[i][j];
	if (i == 0 || j == 0 || i == game->rows - 1 || j == game->cols - 1)
	{
		if (c == '0' || c == game->player)
			return (0);
	}
	if ((j > 0 && is_invalid_neighbor(c, game->map[i][j - 1],
			game->player))
		|| (j < game->cols - 1 && is_invalid_neighbor(c,
			game->map[i][j + 1], game->player))
		|| (i > 0 && is_invalid_neighbor(c, game->map[i - 1][j],
			game->player))
		|| (i < game->rows - 1 && is_invalid_neighbor(c,
			game->map[i + 1][j], game->player)))
		return (0);
	return (1);
}

int	check_wall(t_cub *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			c = game->map[i][j];
			if (c == '0' || c == ' ' || c == game->player)
			{
				if (!check_void(i, j, game))
				{
					write(2, "Error: Map is not closed\n", 26);
					return (-1);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
