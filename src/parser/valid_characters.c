/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 08:05:22 by amagoury          #+#    #+#             */
/*   Updated: 2025/05/24 13:04:56 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_valid_char(char c)
{
	return (c == '1'
		|| c == '0'
		|| c == ' '
		|| c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W');
}

static int	handle_player_char(t_cub *game, char c, int *player_count)
{
	if (*player_count > 0)
		return (1);
	*player_count += 1;
	game->player = c;
	game->p_flag = 1;
	return (0);
}

int	valid_characters(char **map, t_cub *game)
{
	int	i;
	int	j;
	int	player_count;

	i = -1;
	player_count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!is_valid_char(map[i][j]))
				return (write(2, "Error: invalid character\n", 26), 1);
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (handle_player_char(game, map[i][j], &player_count))
					return (1);
			}
		}
	}
	if (player_count == 0)
		return (write(2, "Error: no player found\n", 24), 1);
	return (0);
}


